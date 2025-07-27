#include "SnakePart.hpp"
#include "Entity.hpp"
#include <stdexcept>

SnakePart::SnakePart(int x, int y, Direction dir) : Entity{x,y,GREEN}, m_direction{dir}{}

SnakePart::SnakePart() : Entity{INVALID_POS, INVALID_POS, GREEN}, m_direction{Direction::INVALID}{}

void SnakePart::move() {
  switch (m_direction) {
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
      throw std::logic_error(std::string("Invalid direction in") + __PRETTY_FUNCTION__);
  }

}
