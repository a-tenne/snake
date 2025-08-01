#pragma once

#include "SnakePart.hpp"
#include <vector>

class Snake
{
public:
  static Snake
  create_snake (int x_head, int y_head, Direction dir)
  {

    return Snake (x_head, y_head, dir);
  }
  static Snake
  create_invalid ()
  {

    return Snake (INVALID_POS, INVALID_POS, Direction::INVALID);
  }

  inline void
  set_direction (Direction dir)
  {
    m_head.set_direction (dir);
  }

  inline const SnakePart &
  get_head () const
  {
    return m_head;
  }

  inline const std::vector<SnakePart> &
  get_body () const
  {
    return m_body;
  }

  void move ();
  void eat_fruit ();

private:
  Snake (int x_head, int y_head, Direction dir);
  SnakePart m_head;
  std::vector<SnakePart> m_body;
  SnakePart m_last_pos;
};
