#include "Game.hpp"
#include <SDL3/SDL_init.h>
#include <exception>
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#endif

constexpr const char *NAME = "Snake";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 700;
constexpr unsigned int SDL_FLAGS = SDL_INIT_VIDEO;
constexpr const char *FONT_PATH = "assets/Pixellettersfull-BnJ5.ttf";
constexpr int FRAME_RATE = 10;

int
main (int argc, char *argv[])
{
#ifdef WIN32
  FreeConsole ();
#endif
  try
    {
      Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS, FONT_PATH,
                 FRAME_RATE);
      game.run ();
    }
  catch (const std::exception &e)
    {
#ifdef WIN32
      MessageBoxA (nullptr, e.what (), "FATAL ERROR", MB_OK | MB_ICONERROR);
#else
      std::cerr << "FATAL ERROR: " << e.what () << std::endl;
#endif
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
