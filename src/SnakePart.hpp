#pragma once

#include "Entity.hpp"

constexpr int INVALID_POS = -1;

enum class Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  INVALID
};

class SnakePart : public Entity {
public:
  SnakePart(); // this will have invalid state
  SnakePart(int x, int y, Direction dir);
  inline Direction
  get_direction () const
  {
    return m_direction;
  }

  inline void
  set_direction(Direction dir) {
    m_direction = dir;
  }

  void move();
private:
  Direction m_direction;
};
