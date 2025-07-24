#include "Game.hpp"
#include <SDL3/SDL_init.h>

constexpr const char *NAME = "Snake";
constexpr int WINDOW_WIDTH = 500;
constexpr int WINDOW_HEIGHT = 700;
constexpr unsigned int SDL_FLAGS = SDL_INIT_VIDEO;

int
main (int argc, char *argv[])
{
  Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS);
  game.run ();
  return 0;
}
