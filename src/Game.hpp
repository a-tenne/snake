#pragma once
#include "GameField.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string_view>
class Game
{
public:
  Game (std::string_view title, int width, int height, unsigned int sdl_flags);
  ~Game ();
  void run ();

private:
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  GameField m_field;
  int m_width, m_height;
  bool m_running;

private:
  void handle_event (SDL_Event &event);
};
