#pragma once

#include "Color.hpp"
#include "Point.hpp"
#include "SDL3/SDL_render.h"

class Entity
{
public:
  Entity (int x, int y, Color color);
  void render (SDL_Renderer &renderer, const SDL_FRect &border,
               int side_length) const;
  bool collides (const Entity &other) const;
  bool in_bounds ();

  inline int
  get_x () const
  {
    return m_point.x;
  }

  inline int
  get_y () const
  {
    return m_point.y;
  }

  inline const Point &
  get_point () const
  {
    return m_point;
  }

  inline void
  set_x (int x)
  {
    m_point.x = x;
  }

  inline void
  set_y (int y)
  {
    m_point.y = y;
  }

protected:
  Point m_point;
  Color m_color;
};
