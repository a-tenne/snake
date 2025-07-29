#include "Snake.hpp"

Snake::Snake (int x_head, int y_head, Direction dir)
    : m_head{ x_head, y_head, dir }
{
}

void
Snake::move ()
{
  Direction current_dir = m_head.get_direction ();
  // create a copy of the last element, in case a fruit gets consumed
  m_last_pos = m_body.empty () ? m_head : m_body.back ();
  m_head.move ();
  for (auto &part : m_body)
    {
      part.move ();
      Direction temp = part.get_direction ();
      part.set_direction (current_dir);
      current_dir = temp;
    }
}

void
Snake::eat_fruit ()
{
  m_body.push_back (m_last_pos);
}
