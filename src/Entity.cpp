#include "Entity.hpp"
#include "util.hpp"
#include <algorithm>
#include <format>
#include <stdexcept>

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
                int side_length) const
{
  constexpr auto fn_name = pretty_fn_name ();

  if (m_point.x < 0 || m_point.x >= side_length)
    {
      throw std::logic_error (std::format ("Invalid x coordinate in {}: {}\n",
                                           fn_name, m_point.x));
    }
  if (m_point.y < 0 || m_point.y >= side_length)
    {
      throw std::logic_error (std::format ("Invalid y coordinate in {}: {}\n",
                                           fn_name, m_point.y));
    }
  float cell_width = calculate_dimension (border.w, side_length);
  float cell_height = calculate_dimension (border.h, side_length);
  float cell_size = std::min (cell_width, cell_height);

  SDL_FRect frect;
  frect.h = cell_size;
  frect.w = cell_size;
  frect.x = m_point.x * cell_width + border.x;
  frect.y = m_point.y * cell_height + border.y;
  bool render_success
      = SDL_SetRenderDrawColor (&renderer, m_color.r, m_color.g, m_color.b,
                                m_color.a)
        && SDL_RenderFillRect (&renderer, &frect);
  if (!render_success) [[unlikely]]
    {
      SDL_CUSTOM_ERR ();
    }
}
