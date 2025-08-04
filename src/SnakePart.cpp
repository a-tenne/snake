#include "SnakePart.hpp"
#include "Entity.hpp"
#include "util.hpp"
#include <format>
#include <stdexcept>

SnakePart::SnakePart (int x, int y, Direction dir)
    : Entity{ x, y }, m_direction{ dir }
{
}

void
SnakePart::move ()
{
  constexpr auto fn_name = PRETTY_FN_NAME;

  switch (m_direction)
    {
    case Direction::UP:
      m_point.y -= 1;
      break;
    case Direction::DOWN:
      m_point.y += 1;
      break;
    case Direction::LEFT:
      m_point.x -= 1;
      break;
    case Direction::RIGHT:
      m_point.x += 1;
      break;
    default:
      throw std::logic_error (
          std::format ("Invalid direction in {}", fn_name));
    }
}

SnakePart
SnakePart::create_part (int x, int y, Direction dir)
{
  return SnakePart (x, y, dir);
}

SnakePart
SnakePart::create_invalid ()
{
  return SnakePart (INVALID_POS, INVALID_POS, Direction::INVALID);
}

Direction
SnakePart::get_direction () const
{
  return m_direction;
}

void
SnakePart::set_direction (Direction dir)
{
  m_direction = dir;
}
