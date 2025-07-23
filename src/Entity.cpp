#include "Entity.hpp"

Entity::Entity (int x, int y) : m_x{ x }, m_y{ y } {}

bool
Entity::collides (std::vector<std::unique_ptr<Entity>> &others)
{
  for (auto &other : others)
    {
      if (m_x == other->m_x && m_y == other->m_y)
        {
          return true;
        }
    }
  return false;
}
