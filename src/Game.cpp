#include "Game.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SnakePart.hpp"
#include "util.hpp"
#include <ctime>
#include <format>
#include <stdexcept>
#include <string_view>

constexpr int SIDE_LENGTH = 25;
constexpr int NUM_FRUITS = 4;
constexpr float FONT_SIZE = 60;

Game::Game (std::string_view title, int width, int height,
            SDL_InitFlags sdl_flags, SDL_WindowFlags window_flags,
            std::string_view font_path, int tps, int fps)
    : m_state{ GameState::START }, m_field{ SIDE_LENGTH, NUM_FRUITS }, m_width{ width },
      m_height{ height }, m_tps{ tps }, m_fps{ fps }
{
  constexpr auto fn_name = pretty_fn_name ();
  constexpr auto param_gt_zero
      = [fn_name] (int arg_val, const char *arg_name) {
          if (arg_val <= 0) [[unlikely]]
            {
              throw std::invalid_argument (std::format (
                  "{} <= 0 passed to {}: {}", arg_name, fn_name, arg_val));
            }
        };
  param_gt_zero (width, "Window width");
  param_gt_zero (height, "Window height");
  param_gt_zero (tps, "TPS");
  param_gt_zero (fps, "FPS");

  const bool sdl_correct_init
      = SDL_Init (sdl_flags) && TTF_Init ()
        && SDL_CreateWindowAndRenderer (title.data (), width, height,
                                        window_flags, &m_window, &m_renderer)
        && SDL_GetCurrentTime (&m_time);
  if (!sdl_correct_init) [[unlikely]]
    {
      sdl_exit_error ();
    }
  if (m_font = TTF_OpenFont (font_path.data (), FONT_SIZE); m_font == nullptr)
      [[unlikely]]
    {
      sdl_exit_error ();
    }
  std::srand (static_cast<unsigned int> (std::time (nullptr)));
}

Game::~Game ()
{
  sdl_delete (m_window, SDL_DestroyWindow);
  sdl_delete (m_renderer, SDL_DestroyRenderer);
  sdl_delete (m_font, TTF_CloseFont);
  TTF_Quit ();
  SDL_Quit ();
}

void
Game::run ()
{
  bool text_rendered_once = false;
  const Uint32 frame_rate_ms = 1000 / m_fps;
  while (m_running)
    {
      int old_height = m_height, old_width = m_width;
      SDL_Event event;
      while (SDL_PollEvent (&event))
        {
          handle_event (event);
        }
      if (!m_running)
        {
          return;
        }
      if (old_height != m_height || old_width != m_width)
        {
          text_rendered_once = false;
        }
      switch (m_state)
        {
        case GameState::START:
          if (!text_rendered_once)
            {
              render_start ();
              text_rendered_once = true;
            }
          break;
        case GameState::RUNNING:
          render_running ();
          if (text_rendered_once)
            {
              text_rendered_once = false;
            }
          break;
        case GameState::FINI:
          if (!text_rendered_once)
            {
              render_fini ();
              text_rendered_once = true;
            }
          break;
        }
      if (m_state != GameState::RUNNING && !SDL_GetCurrentTime (&m_time))
          [[unlikely]]
        {
          sdl_exit_error ();
        }
      SDL_Delay (frame_rate_ms);
    }
}

void
Game::handle_event (SDL_Event &event)
{
  switch (event.type)
    {
    case SDL_EVENT_QUIT:
      m_running = false;
      break;
    case SDL_EVENT_WINDOW_RESIZED:
      SDL_GetWindowSize (m_window, &m_width, &m_height);
      break;
    case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
      m_is_fullscreen = true;
      break;
    case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
      m_is_fullscreen = false;
      break;
    case SDL_EVENT_KEY_DOWN:
      switch (event.key.key)
        {
        case SDLK_W:
        case SDLK_UP:
          m_field.change_snake_direction (Direction::UP);
          break;
        case SDLK_A:
        case SDLK_LEFT:
          m_field.change_snake_direction (Direction::LEFT);
          break;
        case SDLK_S:
        case SDLK_DOWN:
          m_field.change_snake_direction (Direction::DOWN);
          break;
        case SDLK_D:
        case SDLK_RIGHT:
          m_field.change_snake_direction (Direction::RIGHT);
          break;
        case SDLK_ESCAPE:
          m_running = false;
          break;
        case SDLK_RETURN:
          SDL_SetWindowFullscreen (m_window, !m_is_fullscreen);
          break;
        case SDLK_SPACE:
          switch (m_state)
            {
            case GameState::START:
            case GameState::FINI:
              m_field.init ();
              m_state = GameState::RUNNING;
              break;
            default:
              break;
            }
          break;
        default:
          break;
        }
      break;
    default:
      break;
    }
}

bool
Game::render_high_score ()
{
  static constinit int last_high_score = -1;
  static std::string text;
  if (last_high_score != m_high_score)
    {
      last_high_score = m_high_score;
      text = std::format ("High Score: {}", last_high_score);
    }
  SDL_Color white = { 255, 255, 255, SDL_ALPHA_OPAQUE };
  surface_unique surface (
      TTF_RenderText_Solid (m_font, text.data (), 0, white));
  if (surface == nullptr) [[unlikely]]
    {
      sdl_exit_error ();
    }
  texture_unique texture (
      SDL_CreateTextureFromSurface (m_renderer, surface.get ()));
  if (texture == nullptr) [[unlikely]]
    {
      sdl_exit_error ();
    }
  float scale = 0.5;
  SDL_FRect rect1 = { .x = 0,
                      .y = 0,
                      .w = static_cast<float> (surface->w * scale),
                      .h = static_cast<float> (surface->h * scale) };
  return SDL_RenderTexture (m_renderer, texture.get (), nullptr, &rect1);
}

void
Game::render_text_fields (std::string_view field1, std::string_view field2,
                          bool show_high_score)
{
  SDL_Color white = { 255, 255, 255, SDL_ALPHA_OPAQUE };

  surface_unique surface1 (
      TTF_RenderText_Solid (m_font, field1.data (), 0, white));
  surface_unique surface2 (
      TTF_RenderText_Solid (m_font, field2.data (), 0, white));
  if (surface1 == nullptr || surface2 == nullptr) [[unlikely]]
    {
      sdl_exit_error ();
    }
  texture_unique texture1 (
      SDL_CreateTextureFromSurface (m_renderer, surface1.get ()));
  texture_unique texture2 (
      SDL_CreateTextureFromSurface (m_renderer, surface2.get ()));
  if (texture1 == nullptr || texture2 == nullptr) [[unlikely]]
    {
      sdl_exit_error ();
    }

  float scale = 1.5f;
  SDL_FRect rect1
      = { .x = static_cast<float> (m_width - surface1->w * scale) / 2,
          .y = static_cast<float> (m_height - surface1->h * scale) / 2,
          .w = static_cast<float> (surface1->w * scale),
          .h = static_cast<float> (surface1->h * scale) };
  SDL_FRect rect2 = { .x = static_cast<float> (m_width - surface2->w) / 2,
                      .y = static_cast<float> (m_height + surface2->h) / 2,
                      .w = static_cast<float> (surface2->w),
                      .h = static_cast<float> (surface2->h) };
  bool render_success
      = SDL_SetRenderDrawColor (m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a)
        && SDL_RenderClear (m_renderer)
        && SDL_RenderTexture (m_renderer, texture1.get (), nullptr, &rect1)
        && SDL_RenderTexture (m_renderer, texture2.get (), nullptr, &rect2);
  if (!render_success) [[unlikely]]
    {
      sdl_exit_error ();
    }
  if (show_high_score && !render_high_score ()) [[unlikely]]
    {
      sdl_exit_error ();
    }
  if (!SDL_RenderPresent (m_renderer)) [[unlikely]]
    {
      sdl_exit_error ();
    }
}

void
Game::render_start ()
{
  constexpr bool SHOW_HIGH_SCORE = false;
  render_text_fields ("Welcome to Snake", "Press Space to start",
                      SHOW_HIGH_SCORE);
}

void
Game::render_fini ()
{
  constexpr bool SHOW_HIGH_SCORE = true;
  render_text_fields ("Game Over", "Press Space to go again", SHOW_HIGH_SCORE);
}

void
Game::render_running ()
{
  static const SDL_Time tick_rate_ms = 1000 / m_tps;
  static constinit SDL_Time accumulator = 0;

  SDL_Time current_time;
  if (!SDL_GetCurrentTime (&current_time)) [[unlikely]]
    {
      sdl_exit_error ();
    }

  time_t current = SDL_NS_TO_MS (current_time),
         previous = SDL_NS_TO_MS (m_time);
  time_t frame_time = current - previous;
  m_time = current_time;

  if (int field_score = m_field.get_score (); m_high_score < field_score)
    {
      m_high_score = m_field.get_score ();
    }

  accumulator += frame_time;

  while (accumulator >= tick_rate_ms)
    {
      m_field.update ();
      accumulator -= tick_rate_ms;
    }
  bool render_success
      = SDL_SetRenderDrawColor (m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a)
        && SDL_RenderClear (m_renderer);

  if (!render_success) [[unlikely]]
    {
      sdl_exit_error ();
    }

  m_field.render (*m_renderer, m_height, m_width);
  if (!render_high_score () || !SDL_RenderPresent (m_renderer)) [[unlikely]]
    {
      sdl_exit_error ();
    }
  if (!m_field.is_snake_alive ())
    {
      m_state = GameState::FINI;
      m_field.clear ();
      accumulator = 0;
    }
}
