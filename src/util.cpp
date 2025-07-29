#include "util.hpp"
#include "SDL3/SDL_error.h"
#include <format>
#include <stdexcept>

void
sdl_exit_error (const char *file_name, int line)
{
  throw std::runtime_error (std::format ("File {} on line {}: {}\n", file_name,
                                         line, SDL_GetError ()));
}
