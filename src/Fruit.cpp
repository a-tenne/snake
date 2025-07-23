#include "Fruit.hpp"
#include "SDL3/SDL_rect.h"

Fruit::Fruit (int x, int y) : Entity{ x, y } {}

void
Fruit::render (SDL_Renderer &renderer, int window_height, int window_width,
               int field_height, int field_width) const
{
  float cellWidth = calculate_dimension (window_width, field_width);
  float cellHeight = calculate_dimension (window_height, field_height);
  float cellSize = std::min (cellWidth, cellHeight);

  SDL_FRect frect;
  frect.h = cellSize;
  frect.w = cellSize;
  frect.x = m_x * cellWidth;
  frect.y = m_y * cellHeight;
  SDL_SetRenderDrawColor (&renderer, 255, 0, 0, 1);
  SDL_RenderRect (&renderer, &frect);
  SDL_RenderFillRect (&renderer, &frect);
}
