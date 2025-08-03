#include "util.hpp"
#include "gtest/gtest.h"
#include <limits>
#include <stdexcept>
#include <string>

TEST (ArithmeticTests, IllegalFirstOperand)
{
  ASSERT_THROW (calculate_dimension (0, 0), std::logic_error);
  ASSERT_THROW (calculate_dimension (-1, 0), std::logic_error);
  ASSERT_THROW (calculate_dimension (std::numeric_limits<int>::min (), 0),
                std::logic_error);
}

TEST (ArithmeticTests, IllegalSecondOperand)
{
  ASSERT_THROW (calculate_dimension (std::numeric_limits<int>::max (), 0),
                std::logic_error);
  ASSERT_THROW (calculate_dimension (std::numeric_limits<int>::max (), -1),
                std::logic_error);
  ASSERT_THROW (calculate_dimension (1, std::numeric_limits<int>::min ()),
                std::logic_error);
}

TEST (ArithmeticTests, SimpleDivision)
{
  ASSERT_EQ (calculate_dimension (10, 5), 2);
  ASSERT_EQ (calculate_dimension (15, 3), 5);
  ASSERT_EQ (calculate_dimension (1200, 20), 60);
}

TEST (ArithmeticTests, CorrectPrecision)
{
  ASSERT_EQ (calculate_dimension (12, 5), 2.4f);
  ASSERT_EQ (calculate_dimension (15, 4), 3.75f);
}

TEST (SDLExitError, SanityCheck)
{
  ASSERT_THROW (sdl_exit_error (), std::runtime_error);
}

extern int global_argc;
extern char **global_argv;

TEST (FontPathTests, FontPathResolves)
{
  std::string path;
  ASSERT_NO_THROW (path = resolve_font_path (global_argc, global_argv););
  ASSERT_FALSE (path.empty ());
}
