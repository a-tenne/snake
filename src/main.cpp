#include "Game.hpp"
#include <SDL3/SDL_init.h>

constexpr const char *NAME = "Snake";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 700;
constexpr unsigned int SDL_FLAGS = SDL_INIT_VIDEO;
constexpr const char *FONT_PATH = "assets/Pixellettersfull-BnJ5.ttf";
constexpr int FRAME_RATE = 10;

int
main (int argc, char *argv[])
{
  Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS, FONT_PATH,
             FRAME_RATE);
  game.run ();
  return 0;
}
