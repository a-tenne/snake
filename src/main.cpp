#include "Game.hpp"
#include <SDL3/SDL_init.h>

#define NAME "Snake"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 700
#define SDL_FLAGS SDL_INIT_VIDEO

int
main (int argc, char *argv[])
{
  Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS);
  game.run ();
  return 0;
}
