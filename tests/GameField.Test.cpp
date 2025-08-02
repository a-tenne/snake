#include <gtest/gtest.h>
#include <limits>
#include <ranges>
#include <stdexcept>
#include "GameField.hpp"
#define SDL_MAIN_HANDLED
#include "SDL3/SDL_render.h"

constexpr int MIN = std::numeric_limits<int>::min();
constexpr int MAX = std::numeric_limits<int>::max();

TEST(GameFieldConstructor, InvalidSideLengthThrows) {
  ASSERT_THROW(GameField (0,1), std::invalid_argument);
  ASSERT_THROW(GameField (-1,1), std::invalid_argument);
  ASSERT_THROW(GameField (MIN,1), std::invalid_argument);
}

TEST(GameFieldConstructor, InvalidNumFruitsThrows) {
  ASSERT_THROW(GameField (1,0), std::invalid_argument);
  ASSERT_THROW(GameField (1,-1), std::invalid_argument);
  ASSERT_THROW(GameField (1,MIN), std::invalid_argument);
}

TEST(GameFieldConstructor, NumFruitsTooBigThrows) {
  ASSERT_THROW(GameField (1,1), std::invalid_argument);
  ASSERT_THROW(GameField (1,MAX), std::invalid_argument);
  ASSERT_THROW(GameField (50,5000), std::invalid_argument);
}

TEST(GameFieldConstructor, ValidConstructors) {
  ASSERT_NO_THROW(GameField (MAX,1));
  ASSERT_NO_THROW(GameField (MAX,50));
}

constexpr int FIELD_SIZE = 50;

struct GameFieldTest : testing::Test {
  GameField field = GameField(FIELD_SIZE,1);
};

TEST_F(GameFieldTest, SnakeInitCleanup) {
  ASSERT_EQ(field.get_score(), 0);
  ASSERT_FALSE(field.is_snake_alive());
  field.init();
  ASSERT_EQ(field.get_score(), 0);
  ASSERT_TRUE(field.is_snake_alive());
  field.clear();
  ASSERT_FALSE(field.is_snake_alive());
}

TEST_F(GameFieldTest, UninitDirChangeThrows) {
  ASSERT_THROW(field.change_snake_direction(Direction::UP), std::logic_error);
  ASSERT_THROW(field.change_snake_direction(Direction::DOWN), std::logic_error);
  ASSERT_THROW(field.change_snake_direction(Direction::LEFT), std::logic_error);
  ASSERT_THROW(field.change_snake_direction(Direction::RIGHT), std::logic_error);
}

TEST_F(GameFieldTest, InvalidDirChangeThrows) {
  field.init();
  ASSERT_THROW(field.change_snake_direction(Direction::INVALID), std::logic_error);
}

TEST_F(GameFieldTest, InvalidRendererThrows) {
  SDL_Renderer *dummy_renderer = nullptr;

  field.init();
  ASSERT_THROW(field.render(*dummy_renderer, 200, 200), std::runtime_error);
}

TEST_F(GameFieldTest, SnakeRunsIntoWall) {
  field.init();
  for(int _ : std::ranges::views::iota(0,FIELD_SIZE)) {
    field.update();
  }
  ASSERT_FALSE(field.is_snake_alive());
}
