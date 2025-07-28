#include "SnakePart.hpp"
#include "Entity.hpp"
#include <stdexcept>
#include <string>

SnakePart::SnakePart(int x, int y, Direction dir) : Entity{x,y,GREEN}, m_direction{dir}{}

SnakePart::SnakePart() : Entity{INVALID_POS, INVALID_POS, GREEN}, m_direction{Direction::INVALID}{}

void SnakePart::move() {
  #if defined(__clang__) || defined(__GNUC__)
    constexpr const char *fn_name = __PRETTY_FUNCTION__;
  #elif defined(_MSC_VER)
    constexpr const char *fn_name = __FUNCSIG__;
  #endif

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
      throw std::logic_error(std::string("Invalid direction in") + fn_name);
  }

}
