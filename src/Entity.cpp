#include "Entity.hpp"
#include <algorithm>

Entity::Entity (int x, int y, const Color&color) : m_point{x,y}, m_color(color) {}

bool
Entity::collides (const Entity &other) const
{
    return m_point == other.m_point;
}

void
Entity::render (SDL_Renderer &renderer, int window_height, int window_width,
               int field_height, int field_width) const
{
  float cellWidth = calculate_dimension (window_width, field_width);
  float cellHeight = calculate_dimension (window_height, field_height);
  float cellSize = std::min (cellWidth, cellHeight);

  SDL_FRect frect;
  frect.h = cellSize;
  frect.w = cellSize;
  frect.x = m_point.x * cellWidth;
  frect.y = m_point.y * cellHeight;
  SDL_SetRenderDrawColor (&renderer, m_color.r, m_color.g, m_color.b,m_color.a);
  SDL_RenderRect (&renderer, &frect);
  SDL_RenderFillRect (&renderer, &frect);
}
