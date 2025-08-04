#include "Snake.hpp"
#include "SnakeMovementTuple.hpp"
#include "SnakePart.hpp"
#include "gtest/gtest.h"
#include <ranges>
#include <stdexcept>

struct SnakeMoveTest : testing::Test
{
  Snake snake;
  SnakeMoveTest () : snake{ Snake::create_snake (0, 0, Direction::INVALID) } {}
};

TEST_F (SnakeMoveTest, InvalidThrows)
{
  EXPECT_THROW (snake.move (), std::logic_error);
}

TEST_F (SnakeMoveTest, BiggerSnakeMoves)
{
  constexpr auto range = std::views::iota;
  snake.set_direction (Direction::RIGHT);
  for ([[maybe_unused]] int _ : range (0, 5))
    {
      snake.move ();
      snake.eat_fruit ();
    }
  Snake old = snake;
  snake.move ();
  ASSERT_NE (snake.get_head ().get_point (), old.get_head ().get_point ());
  for (int i : range (0, 5))
    {
      const SnakePart &new_part = snake.get_body ().at (i),
                      &old_part = old.get_body ().at (i);
      ASSERT_NE (new_part.get_point (), old_part.get_point ());
    }
}

struct SnakeMoveParamTest : SnakeMoveTest,
                            testing::WithParamInterface<SnakeMovementTuple>
{
  SnakeMoveParamTest () { snake.set_direction (GetParam ().dir); }
};

TEST_P (SnakeMoveParamTest, MovesCorrectly)
{
  snake.move ();
  EXPECT_EQ (snake.get_head ().get_point (), GetParam ().expected);
}

TEST_P (SnakeMoveParamTest, MultipleMoves)
{
  auto [dir, point] = GetParam ();
  switch (dir)
    {
    case Direction::UP:
    case Direction::DOWN:
      point.y *= 10;
      break;
    case Direction::LEFT:
    case Direction::RIGHT:
      point.x *= 10;
      break;
    case Direction::INVALID:
      FAIL ();
      break;
    }
  snake.set_direction (dir);
  for ([[maybe_unused]] int _ : std::views::iota (0, 10))
    {
      snake.move ();
    }
  EXPECT_EQ (snake.get_head ().get_point (), point);
}

INSTANTIATE_TEST_SUITE_P (MovesUp, SnakeMoveParamTest,
                          testing::Values (SnakeMovementTuple{ Direction::UP,
                                                               { 0, -1 } }));
INSTANTIATE_TEST_SUITE_P (MovesDown, SnakeMoveParamTest,
                          testing::Values (SnakeMovementTuple{ Direction::DOWN,
                                                               { 0, 1 } }));
INSTANTIATE_TEST_SUITE_P (MovesLeft, SnakeMoveParamTest,
                          testing::Values (SnakeMovementTuple{ Direction::LEFT,
                                                               { -1, 0 } }));
INSTANTIATE_TEST_SUITE_P (MovesRight, SnakeMoveParamTest,
                          testing::Values (SnakeMovementTuple{
                              Direction::RIGHT, { 1, 0 } }));
struct SnakeFruitTest : testing::Test
{
  Snake snake = Snake::create_snake (1, 1, Direction::RIGHT);
};

TEST_F (SnakeFruitTest, FirstTickThrows)
{
  EXPECT_THROW (snake.eat_fruit (), std::logic_error);
}

TEST_F (SnakeFruitTest, EatAfterMove)
{
  SnakePart last_pos = snake.get_head ();
  snake.move ();
  snake.eat_fruit ();
  ASSERT_EQ (snake.get_body ().size (), 1);
  ASSERT_EQ (snake.get_body ().at (0).get_point (), last_pos.get_point ());
}
TEST_F (SnakeFruitTest, ConsecutiveEatThrows)
{
  snake.move ();
  snake.eat_fruit ();
  EXPECT_THROW (snake.eat_fruit (), std::logic_error);
}
