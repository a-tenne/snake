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
