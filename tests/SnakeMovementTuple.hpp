#pragma once
#include "SnakePart.hpp"
#include <ostream>
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

