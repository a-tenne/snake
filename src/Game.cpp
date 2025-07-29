#include "Game.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SnakePart.hpp"
#include "util.hpp"
#include <ctime>
#include <format>
#include <stdexcept>

constexpr int SIDE_LENGTH = 35;
constexpr int NUM_FRUITS = 4;

Game::Game (std::string_view title, int width, int height,
            unsigned int sdl_flags, std::string_view font_path, int frame_rate)
    : m_width{ width }, m_height{ height }, m_running{ true },
      m_field{ SIDE_LENGTH, NUM_FRUITS }, m_state{ GameState::START },
      m_frame_rate{ frame_rate }, m_is_fullscreen{ false }
{
  constexpr auto fn_name = pretty_fn_name ();

  if (width <= 0)
    {
      throw std::invalid_argument (std::format (
          "Window width <= 0 passed to {}: {}\n", fn_name, width));
    }
  if (height <= 0)
    {
      throw std::invalid_argument (std::format (
          "Window height <= 0 passed to {}: {}\n", fn_name, height));
    }
  if (frame_rate <= 0)
    {
      throw std::invalid_argument (std::format (
          "Frame rate <= 0 passed to {}: {}\n", fn_name, frame_rate));
    }
  if (!SDL_Init (sdl_flags)
      || !SDL_CreateWindowAndRenderer (title.data (), width, height,
                                       SDL_WINDOW_RESIZABLE, &m_window,
                                       &m_renderer)
      || !TTF_Init ())
    {
      sdl_exit_error ("SDL ERROR: ");
    }

  if (m_font = TTF_OpenFont (font_path.data (), 60); m_font == nullptr)
    {
      sdl_exit_error ("TTF ERROR: ");
    }
  std::srand (static_cast<unsigned int> (std::time (nullptr)));
}

Game::~Game ()
{
  SDL_DestroyWindow (m_window);
  SDL_DestroyRenderer (m_renderer);
  TTF_CloseFont (m_font);
  TTF_Quit ();
  SDL_Quit ();
}

void
Game::run ()
{
  bool text_rendered_once = false;
  while (m_running)
    {
      int old_height = m_height, old_width = m_width;
      SDL_Event event;
      while (SDL_PollEvent (&event))
        {
          handle_event (event);
        }
      if (!m_running)
        return;
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
      SDL_Delay (1000 / m_frame_rate);
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

void
Game::render_text_fields (const char *field1, const char *field2)
{
  SDL_Color white = { 255, 255, 255, SDL_ALPHA_OPAQUE };
  std::unique_ptr<SDL_Surface, void (*) (SDL_Surface *)> surface1 (
      TTF_RenderText_Solid (m_font, field1, 0, white), SDL_DestroySurface);
  std::unique_ptr<SDL_Surface, void (*) (SDL_Surface *)> surface2 (
      TTF_RenderText_Solid (m_font, field2, 0, white), SDL_DestroySurface);
  if (surface1 == nullptr || surface2 == nullptr)
    {
      sdl_exit_error ("TTF ERROR: ");
    }
  std::unique_ptr<SDL_Texture, void (*) (SDL_Texture *)> texture1 (
      SDL_CreateTextureFromSurface (m_renderer, surface1.get ()),
      SDL_DestroyTexture);
  std::unique_ptr<SDL_Texture, void (*) (SDL_Texture *)> texture2 (
      SDL_CreateTextureFromSurface (m_renderer, surface2.get ()),
      SDL_DestroyTexture);
  if (texture1 == nullptr || texture2 == nullptr)
    {
      sdl_exit_error ("SDL ERROR: ");
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
  SDL_SetRenderDrawColor (m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
  SDL_RenderClear (m_renderer);
  SDL_RenderTexture (m_renderer, texture1.get (), nullptr, &rect1);
  SDL_RenderTexture (m_renderer, texture2.get (), nullptr, &rect2);
  SDL_RenderPresent (m_renderer);
}

void
Game::render_start ()
{
  render_text_fields ("Welcome to Snake", "Press Space to start");
}

void
Game::render_fini ()
{
  render_text_fields ("Game Over", "Press Space to go again");
}

void
Game::render_running ()
{
  SDL_SetRenderDrawColor (m_renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
  SDL_RenderClear (m_renderer);
  m_field.update ();
  if (!m_field.is_snake_alive ())
    {
      m_state = GameState::FINI;
      m_field.clear ();
      return;
    }
  m_field.render (*m_renderer, m_height, m_width);
  SDL_RenderPresent (m_renderer);
}

void
Game::sdl_exit_error (std::string_view error_msg)
{
  throw std::runtime_error (
      std::format ("{}: {}\n", error_msg, SDL_GetError ()));
}
