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


std::string
resolve_font_path (int argc, char *const argv[])
{
constexpr const char *BASE_PATH = {
#ifdef WIN32
  "assets\\Pixellettersfull-BnJ5.ttf"
#else
  "assets/Pixellettersfull-BnJ5.ttf"
#endif
};
#ifdef WIN32
  constexpr char separator = '\\';
#else
  constexpr char separator = '/';
#endif
  if (argc < 1) [[unlikely]]
    {
      throw std::invalid_argument ("Program startup path unavailable.");
    }
  std::string path (argv[0]);
  if (!path.contains (separator)) [[unlikely]]
    {
      throw std::invalid_argument (
          std::format ("Malformed program startup path: {}",
                       path.empty () ? "<EMPTY PATH>" : path));
    }
  return path.erase (path.find_last_of (separator) + 1) + BASE_PATH;
}
