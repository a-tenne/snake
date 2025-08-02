#pragma once

#if defined(__clang__) || defined(__GNUC__)
#define PRETTY_FN_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define PRETTY_FN_NAME __FUNCSIG__
#else 
#define PRETTY_FN_NAME __FUNCTION__
#endif

void sdl_exit_error ();
float calculate_dimension (int window_dimension, int field_dimension);
