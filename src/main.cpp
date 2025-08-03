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
      // This constructor has a lot of parameters in order to facilitate unit
      // testing
      Game game (config::NAME, config::WINDOW_WIDTH, config::WINDOW_HEIGHT,
                 config::SDL_FLAGS, config::WINDOW_FLAGS, font_path,
                 config::TICKS_PER_SECOND, config::FRAME_RATE);
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
