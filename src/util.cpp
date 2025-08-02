#include "util.hpp"
#include "SDL3/SDL_error.h"
#include <format>
#include <stdexcept>
#include <algorithm>

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
  "assets/Pixellettersfull-BnJ5.ttf"
};
constexpr char unix_separator = '/';
  constexpr char win_separator = '\\';
  if (argc < 1) [[unlikely]]
    {
      throw std::invalid_argument ("Program startup path unavailable.");
    }
  std::string path (argv[0]);
  std::replace(path.begin(), path.end(), win_separator, unix_separator);
  if ((path.contains (unix_separator) && path.contains(win_separator)) || path.empty()) [[unlikely]]
    {
      throw std::invalid_argument (
          std::format ("Malformed program startup path: {}",
                       path.empty () ? "<EMPTY PATH>" : path));
    }
  return path.erase(path.find_last_of(unix_separator) + 1) + BASE_PATH;
}
