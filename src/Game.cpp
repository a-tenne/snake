#include "Game.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"

Game::Game (std::string_view title, int width, int height)
    : m_width (width), m_height (height)
{
  SDL_Init (SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer (title.data (), width, height,
                               SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
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
  bool running = true;
  while (running)
    {
      SDL_Event event;
      while (SDL_PollEvent (&event))
        {
          switch (event.type)
            {
            case SDL_EVENT_QUIT:
              running = false;
              break;
            default:
              break;
            }
        }
      SDL_RenderClear (m_renderer);
      SDL_RenderPresent (m_renderer);
    }
}
