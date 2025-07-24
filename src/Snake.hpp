#pragma once

#include "Fruit.hpp"
#include "SnakePart.hpp"

enum class direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Snake
{
public:
  Snake (int x_head, int y_head, direction dir);

  inline direction
  get_direction () const
  {
    return m_dir;
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

  void consume_fruit (const Fruit &fruit);
  void append_body(int x, int y);
private:
  SnakePart m_head;
  std::vector<SnakePart> m_body;
  direction m_dir;
};
