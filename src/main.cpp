#include "Game.hpp"
#include "config.hpp"
#include "util.hpp"
#include <SDL3/SDL_init.h>
#include <exception>
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#endif

int
main (int argc, char *const argv[])

{
#ifdef WIN32
  FreeConsole ();
#endif
  try
    {
      std::string font_path = resolve_font_path (argc, argv);
      using namespace config;
      Game game (NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_FLAGS, WINDOW_FLAGS,
                 font_path, TICKS_PER_SECOND, FRAME_RATE);
      game.run ();
    }
  catch (const std::exception &e)
    {
#ifdef WIN32
      MessageBoxA (nullptr, e.what (), "FATAL ERROR", MB_OK | MB_ICONERROR);
#else
      std::cerr << e.what () << std::endl;
#endif
      return EXIT_FAILURE;
    }
}
