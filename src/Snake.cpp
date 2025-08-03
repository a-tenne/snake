#include "Snake.hpp"
#include "SnakePart.hpp"
#include <stdexcept>

Snake::Snake (int x_head, int y_head, Direction dir)
    : m_head{ SnakePart::create_part (x_head, y_head, dir) },
      m_last_pos{ SnakePart::create_invalid () }
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
  if (m_last_pos.get_direction () == Direction::INVALID) [[unlikely]]
    {
      throw std::logic_error (
          "Snake cannot consume a fruit before moving");
    }
  m_body.push_back (m_last_pos);
  m_last_pos = SnakePart::create_invalid ();
}
