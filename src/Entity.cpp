#include "Entity.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>

Entity::Entity (int x, int y, Color color) : m_point{ x, y }, m_color (color)
{
}

bool
Entity::collides (const Entity &other) const
{
  return m_point == other.m_point;
}

void
Entity::render (SDL_Renderer &renderer, const SDL_FRect &border,
                int field_height, int field_width) const
{
  if(m_point.x < 0) {
    throw std::logic_error(std::string("Invalid x coordinate in ") + __PRETTY_FUNCTION__ + ": " + std::to_string(m_point.x));
  }
  if(m_point.y < 0) {
    throw std::logic_error((std::string("Invalid y coordinate in ") + __PRETTY_FUNCTION__ + ": " + std::to_string(m_point.y)));
  }
  float cell_width = calculate_dimension (border.w, field_width);
  float cell_height = calculate_dimension (border.h, field_height);
  float cell_size = std::min (cell_width, cell_height);

  SDL_FRect frect;
  frect.h = cell_size;
  frect.w = cell_size;
  frect.x = m_point.x * cell_width + border.x;
  frect.y = m_point.y * cell_height + border.y;
  SDL_SetRenderDrawColor (&renderer, m_color.r, m_color.g, m_color.b,
                          m_color.a);
  SDL_RenderRect (&renderer, &frect);
  SDL_RenderFillRect (&renderer, &frect);
}
