#pragma once

#include "SnakePart.hpp"

class Snake
{
public:
  Snake (int x_head, int y_head, Direction dir);
  Snake() = default; // this will have invalid state

  inline void
  set_direction (Direction dir) 
  {
    m_head.set_direction(dir);
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

  void move();
  void eat_fruit();
private:
  SnakePart m_head;
  std::vector<SnakePart> m_body;
  SnakePart m_last_pos;
};
