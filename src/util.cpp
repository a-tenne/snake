#include "util.hpp"
#include "SDL3/SDL_error.h"
#include <format>
#include <stdexcept>

void
sdl_exit_error ()
{
  throw std::runtime_error (std::format ("SDL ERROR {}", SDL_GetError ()));
}

float
calculate_dimension (int window_dimension, int field_dimension)
{
  return static_cast<float> (window_dimension)
         / static_cast<float> (field_dimension);
}
