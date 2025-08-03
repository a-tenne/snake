#include "util.hpp"
#include "gtest/gtest.h"
#include <limits>
#define SDL_MAIN_HANDLED
#include "Game.hpp"
#include <stdexcept>
#include <string>

constexpr int MIN = std::numeric_limits<int>::min ();
constexpr const char *TITLE = "test";
constexpr int DEFAULT_WIDTH = 100, DEFAULT_HEIGHT = 100, DEFAULT_TPS = 20,
              DEFAULT_FPS = 60;
constexpr SDL_InitFlags INIT_FLAGS = 0;
constexpr SDL_WindowFlags WINDOW_FLAGS = 0;

extern int global_argc;
extern char **global_argv;

struct GameConstructorTests : testing::Test, testing::WithParamInterface<int>
{
  std::string font_path;
  GameConstructorTests ()
  {
    font_path = resolve_font_path (global_argc, global_argv);
  }
};

TEST_P (GameConstructorTests, InvalidWidth)
{
  ASSERT_THROW (Game (TITLE, GetParam (), DEFAULT_HEIGHT, INIT_FLAGS,
                      WINDOW_FLAGS, font_path, DEFAULT_TPS, DEFAULT_FPS),
                std::invalid_argument);
}

TEST_P (GameConstructorTests, InvalidHeight)
{
  ASSERT_THROW (Game (TITLE, DEFAULT_WIDTH, GetParam (), INIT_FLAGS,
                      WINDOW_FLAGS, font_path, DEFAULT_TPS, DEFAULT_FPS),
                std::invalid_argument);
}

TEST_P (GameConstructorTests, InvalidTPS)
{
  ASSERT_THROW (Game (TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT, INIT_FLAGS,
                      WINDOW_FLAGS, font_path, GetParam (), DEFAULT_FPS),
                std::invalid_argument);
}

TEST_P (GameConstructorTests, InvalidFPS)
{
  ASSERT_THROW (Game (TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT, INIT_FLAGS,
                      WINDOW_FLAGS, font_path, DEFAULT_TPS, GetParam ()),
                std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P (InvalidIntArgs, GameConstructorTests,
                          testing::Values (0, -1, MIN));

TEST_F (GameConstructorTests, InvalidFontPath)
{
  ASSERT_THROW (Game (TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT, INIT_FLAGS,
                      WINDOW_FLAGS, "", DEFAULT_TPS, DEFAULT_FPS),
                std::runtime_error);
}
TEST_F (GameConstructorTests, ValidConstructor)
{
  ASSERT_NO_THROW (Game (TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT, INIT_FLAGS,
                         WINDOW_FLAGS, font_path, DEFAULT_TPS, DEFAULT_FPS));
}
