#include "SnakePart.hpp"
#include "Entity.hpp"
#include "util.hpp"
#include <format>
#include <stdexcept>

SnakePart::SnakePart (int x, int y, Direction dir)
    : Entity{ x, y, colors::GREEN }, m_direction{ dir }
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
