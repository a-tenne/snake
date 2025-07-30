#include "SnakePart.hpp"
#include "Entity.hpp"
#include "util.hpp"
#include <format>
#include <stdexcept>

SnakePart::SnakePart (int x, int y, Direction dir)
    : Entity{ x, y, GREEN }, m_direction{ dir }
{
}

SnakePart::SnakePart ()
    : Entity{ INVALID_POS, INVALID_POS, GREEN },
      m_direction{ Direction::INVALID }
{
}

void
SnakePart::move ()
{
  constexpr auto fn_name = pretty_fn_name ();
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
    [[unlikely]] default:
      throw std::logic_error (
          std::format ("Invalid direction in {}", fn_name));
    }
}
