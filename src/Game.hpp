#pragma once
#define SDL_MAIN_HANDLED
#include "GameField.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string_view>
class Game
{
public:
  Game (std::string_view title, int width, int height, unsigned int sdl_flags,
        std::string_view font_path, int ticks_per_second);
  ~Game ();
  void run ();

private:
  enum class GameState
  {
    START,
    RUNNING,
    FINI
  } m_state;
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  TTF_Font *m_font = nullptr;
  GameField m_field;
  int m_width, m_height;
  const int m_ticks_per_second;
  bool m_running, m_is_fullscreen;
  SDL_Time m_time;

private:
  void handle_event (SDL_Event &event);
  void render_start ();
  void render_running ();
  void render_fini ();
  void render_text_fields (const char *field1, const char *field2);
  void sdl_exit_error (std::string_view error_msg);
};
