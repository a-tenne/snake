#include "Entity.hpp"
#include "util.hpp"
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
  constexpr auto fn_name = PRETTY_FN_NAME;

  if (m_point.x < 0 || m_point.x >= side_length) [[unlikely]]
    {
      throw std::logic_error (
          std::format ("Invalid x coordinate in {}: {}", fn_name, m_point.x));
    }

  if (m_point.y < 0 || m_point.y >= side_length) [[unlikely]]
    {
      throw std::logic_error (
          std::format ("Invalid y coordinate in {}: {}", fn_name, m_point.y));
    }

  if (border.w != border.h) [[unlikely]]
    {
      throw std::logic_error (
          std::format ("Border width in {} is {} and height is {}. They "
                       "should be the same",
                       fn_name, border.w, border.h));
    }
  float cell_size
      = calculate_dimension (static_cast<int> (border.w), side_length);

  SDL_FRect frect;
  frect.h = cell_size;
  frect.w = cell_size;
  // scale the logical coordinates with the side and offset by border
  frect.x = m_point.x * cell_size + border.x;
  frect.y = m_point.y * cell_size + border.y;

  bool render_success
      = SDL_SetRenderDrawColor (&renderer, m_color.r, m_color.g, m_color.b,
                                m_color.a)
        && SDL_RenderFillRect (&renderer, &frect);
  if (!render_success) [[unlikely]]
    {
      sdl_exit_error ();
    }
}
