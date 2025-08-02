#include "SnakePart.hpp"
#include <gtest/gtest.h>
#include <ranges>
#include <stdexcept>
#include "SnakeMovementTuple.hpp"

struct SnakePartTest : testing::Test {
  SnakePart part;
  SnakePartTest() : part{SnakePart::create_part(0, 0, Direction::INVALID)}{}
};

TEST_F(SnakePartTest, InvalidThrows) {
  EXPECT_THROW(part.move(), std::logic_error);
}
struct SnakePartParamTest : SnakePartTest,
                            testing::WithParamInterface<SnakeMovementTuple>
{
  SnakePartParamTest () { part.set_direction (GetParam ().dir); }
};

TEST_P (SnakePartParamTest, MovesCorrectly)
{
  part.move ();
  EXPECT_EQ (part.get_point (), GetParam ().expected);
}

TEST_P (SnakePartParamTest, MultipleMoves)
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
  part.set_direction (dir);
  for ([[maybe_unused]]int _ : std::ranges::views::iota (0, 10))
    {
      part.move ();
    }
  EXPECT_EQ (part.get_point (), point);
}

INSTANTIATE_TEST_SUITE_P (MovesUp, SnakePartParamTest,
                         testing::Values (SnakeMovementTuple{ Direction::UP,
                                                              { 0, -1 } }));
INSTANTIATE_TEST_SUITE_P (MovesDown, SnakePartParamTest,
                         testing::Values (SnakeMovementTuple{ Direction::DOWN,
                                                              { 0, 1 } }));
INSTANTIATE_TEST_SUITE_P (MovesLeft, SnakePartParamTest,
                         testing::Values (SnakeMovementTuple{ Direction::LEFT,
                                                              { -1, 0 } }));
INSTANTIATE_TEST_SUITE_P (MovesRight, SnakePartParamTest,
                         testing::Values (SnakeMovementTuple{ Direction::RIGHT,
                                                              { 1, 0 } }));
