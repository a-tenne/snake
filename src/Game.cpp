#include "Game.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

constexpr int FIELD_WIDTH = 25;
constexpr int FIELD_HEIGHT = 25;

Game::Game (std::string_view title, int width, int height,
            unsigned int sdl_flags)
    : m_width{ width }, m_height{ height },
      m_field{ FIELD_WIDTH, FIELD_HEIGHT }
{
  if (!SDL_Init (sdl_flags)
      || !SDL_CreateWindowAndRenderer (title.data (), width, height,
                                       SDL_WINDOW_RESIZABLE, &m_window,
                                       &m_renderer))
    {
      std::cerr << "ERROR: " << SDL_GetError ();
      std::exit (EXIT_FAILURE);
    }
  std::srand (std::time (nullptr));
}

Game::~Game ()
{
  SDL_DestroyWindow (m_window);
  SDL_DestroyRenderer (m_renderer);
  SDL_Quit ();
}

void
Game::run ()
{
  m_running = true;
  while (m_running)
    {
      SDL_Event event;
      while (SDL_PollEvent (&event))
        {
          handle_event (event);
        }
      m_field.clear ();
      m_field.spawn_fruit ();
      m_field.spawn_fruit ();
      m_field.spawn_fruit ();
      SDL_SetRenderDrawColor (m_renderer, 0, 0, 0, 1);
      SDL_RenderClear (m_renderer);
      m_field.render (*m_renderer, m_height, m_width);
      SDL_RenderPresent (m_renderer);
      SDL_Delay (200);
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
    default:
      break;
    }
}
