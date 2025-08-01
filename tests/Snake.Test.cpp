#include "Snake.hpp"
#include "SnakePart.hpp"
#include <gtest/gtest.h>
#include <ostream>
#include <ranges>
#include <stdexcept>

struct SnakeMovementTuple
{
  Direction dir;
  Point expected;
  friend std::ostream &
  operator<< (std::ostream &os, const SnakeMovementTuple &tuple)
  {
    const char *dir_str = nullptr;
    switch (tuple.dir)
      {
      case Direction::UP:
        dir_str = "UP";
        break;
      case Direction::DOWN:
        dir_str = "DOWN";
        break;
      case Direction::LEFT:
        dir_str = "LEFT";
        break;
      case Direction::RIGHT:
        dir_str = "RIGHT";
        break;
      case Direction::INVALID:
        dir_str = "INVALID";
        break;
      }
    return os << "Direction: " << dir_str << " Point: {" << tuple.expected.x
              << ", " << tuple.expected.y << "}";
  }
};

struct SnakeMoveTest : testing::Test
{
  Snake snake;
  SnakeMoveTest () : snake{Snake::create_snake(0, 0, Direction::INVALID)} {}
};

TEST_F (SnakeMoveTest, InvalidThrows)
{
  EXPECT_THROW (snake.move (), std::logic_error);
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
      point.y -= 9;
      break;
    case Direction::DOWN:
      point.y += 9;
      break;
    case Direction::LEFT:
      point.x -= 9;
      break;
    case Direction::RIGHT:
      point.x += 9;
      break;
    case Direction::INVALID:
      FAIL ();
      break;
    }
  snake.set_direction (dir);
  for ([[maybe_unused]]int _ : std::ranges::views::iota (0, 10))
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
                         testing::Values (SnakeMovementTuple{ Direction::RIGHT,
                                                              { 1, 0 } }));
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
  ASSERT_EQ (snake.get_body ().at (0).get_point (), last_pos.get_point());
}
TEST_F (SnakeFruitTest, ConsecutiveEatThrows) 
{
  snake.move ();
  snake.eat_fruit ();
  EXPECT_THROW(snake.eat_fruit (), std::logic_error);
}
