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

class SnakePart : public Entity
{
public:
  static inline SnakePart create_invalid() {
    return SnakePart(INVALID_POS, INVALID_POS, Direction::INVALID);
  }
  static inline SnakePart create_part(int x, int y, Direction dir) {
    return SnakePart(x,y,dir);
  }
  inline Direction
  get_direction () const
  {
    return m_direction;
  }

  inline void
  set_direction (Direction dir)
  {
    m_direction = dir;
  }

  void move ();

private:
  SnakePart (int x, int y, Direction dir);
  Direction m_direction;
};
