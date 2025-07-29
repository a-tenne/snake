#pragma once
#define SDL_CUSTOM_ERR() sdl_exit_error (__FILE_NAME__, __LINE__)

void sdl_exit_error (const char *file_name, int line);

constexpr const char *
pretty_fn_name ()
{
#if defined(__clang__) || defined(__GNUC__)
  return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
  return __FUNCSIG__;
#endif
}

inline float
calculate_dimension (int window_dimension, int field_dimension)
{
  return static_cast<float> (window_dimension)
         / static_cast<float> (field_dimension);
}
