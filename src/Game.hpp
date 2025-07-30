#pragma once
#define SDL_MAIN_HANDLED
#include "GameField.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3/SDL.h>
#include <string_view>

class Game
{
public:
  Game (std::string_view title, int width, int height, SDL_InitFlags sdl_flags,
        SDL_WindowFlags window_flags, std::string_view font_path, int fps,
        int tps);
  ~Game ();
  void run ();

private:
  template <typename T>
  static void
  sdl_delete (T *ptr, void (*deleter) (T *))
  {
    if (ptr != nullptr)
      {
        deleter (ptr);
      }
  }

  template <typename T, void (*F) (T *)> struct SDL_deleter
  {
    void
    operator() (T *ptr)
    {
      if (ptr != nullptr)
        {
          F (ptr);
        }
    }
  };

  template <typename T, void (*F) (T *)>
  using sdl_unique = std::unique_ptr<T, SDL_deleter<T, F>>;

  using surface_unique = sdl_unique<SDL_Surface, SDL_DestroySurface>;
  using texture_unique = sdl_unique<SDL_Texture, SDL_DestroyTexture>;

  enum class GameState
  {
    START,
    RUNNING,
    FINI
  } m_state;
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  TTF_Font *m_font;
  GameField m_field;
  int m_width, m_height, m_high_score = 0;
  const int m_tps, m_fps;
  bool m_running = true, m_is_fullscreen = false;
  SDL_Time m_time;

private:
  void handle_event (SDL_Event &event);
  void render_start ();
  void render_running ();
  void render_fini ();
  bool render_high_score ();
  void render_text_fields (std::string_view field1, std::string_view field2,
                           bool show_high_score);
};
