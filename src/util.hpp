#pragma once

constexpr const char *
pretty_fn_name ()
{
#if defined(__clang__) || defined(__GNUC__)
  return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
  return __FUNCSIG__;
#endif
}

void sdl_exit_error ();
float calculate_dimension (int window_dimension, int field_dimension);
