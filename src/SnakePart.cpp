#include "SnakePart.hpp"
#include "Entity.hpp"
#include "colors.hpp"
#include <cstdlib>
#include <iostream>

SnakePart::SnakePart(int x, int y, Direction dir) : Entity{x,y,GREEN}, m_direction{dir}{}

SnakePart::SnakePart() : Entity{INVALID_POS, INVALID_POS, GREEN}, m_direction{Direction::INVALID}{}
void SnakePart::move() {
  switch (m_direction) {
    case Direction::UP:
      m_y -= 1;
      break;
    case Direction::DOWN:
      m_y += 1;
      break;
    case Direction::LEFT:
      m_x -= 1;
      break;
    case Direction::RIGHT:
      m_x += 1;
      break;
    default:
      std::cerr << "Invalid Direction" << std::endl;
      std::exit(EXIT_FAILURE);
  }

}
