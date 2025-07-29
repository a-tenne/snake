#include "Game.hpp"
#include <SDL3/SDL_init.h>
#include <exception>
#include <format>
#include <iostream>
#include <string>

#ifdef WIN32
#include <Windows.h>

constexpr const char *FONT_PATH = "assets\\Pixellettersfull-BnJ5.ttf";
#else
constexpr const char *FONT_PATH = "assets/Pixellettersfull-BnJ5.ttf";
#endif

constexpr const char *NAME = "Snake";
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 700;
constexpr unsigned int SDL_FLAGS = SDL_INIT_VIDEO;

constexpr int FRAME_RATE = 10;

int
main (int argc, char *argv[])

{
#ifdef WIN32
  FreeConsole ();
  constexpr char separator = '\\';
#else
  constexpr char separator = '/';
#endif
  try
    {
      if (argc < 1)
        {
          throw std::invalid_argument ("Program startup path unavailable.");
        }
      std::string path (argv[0]);
      if (!path.contains (separator))
        {
          throw std::invalid_argument (
              std::format ("Malformed program startup path: {}",
                           path.empty () ? "<EMPTY PATH>" : path));
        }
      path = path.erase (path.find_last_of (separator) + 1);
      Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS,
                 path + FONT_PATH, FRAME_RATE);
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
