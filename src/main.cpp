#include "Game.hpp"
#include <SDL3/SDL_init.h>

constexpr const char *NAME = "Snake";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 700;
constexpr unsigned int SDL_FLAGS = SDL_INIT_VIDEO;
#ifdef NDEBUG
  constexpr const char *FONT_PATH = "Pixellettersfull-BmJ5.ttf";
#else
  constexpr const char *FONT_PATH = "../src/Pixellettersfull-BnJ5.ttf";
#endif
constexpr int FRAME_RATE = 10;

int
main (int argc, char *argv[])
{
  Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS, FONT_PATH, FRAME_RATE);
  game.run ();
  return 0;
}
