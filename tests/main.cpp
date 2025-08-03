#include "gtest/gtest.h"

int global_argc = 0;
char **global_argv = nullptr;

int
main (int argc, char *argv[])
{
  testing::InitGoogleTest (&argc, argv);
  global_argc = argc;
  global_argv = argv;
  return RUN_ALL_TESTS ();
}
