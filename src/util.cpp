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
  constexpr auto fn_name = PRETTY_FN_NAME;
  if (window_dimension <= 0) [[unlikely]]
    {
      throw std::logic_error (
          std::format ("Illegal parameter window_dimension {} in: {}",
                       window_dimension, fn_name));
    }
  if (field_dimension <= 0) [[unlikely]]
    {
      throw std::logic_error (
          std::format ("Illegal parameter field_dimension {} in: {}",
                       field_dimension, fn_name));
    }
  return static_cast<float> (window_dimension)
         / static_cast<float> (field_dimension);
}
