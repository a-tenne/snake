#pragma once

#include "SDL3/SDL_render.h"
#include <memory>
#include <vector>
#include "colors.hpp"

class Entity
{
public:
  Entity (int x, int y, const Color&color);
  void render (SDL_Renderer &renderer, int window_height, int window_width,
               int field_height, int field_width) const;
  bool collides (std::vector<std::unique_ptr<Entity>> &others);
  bool in_bounds ();

  inline int
  get_x ()
  {
    return m_x;
  }

  inline int
  get_y ()
  {
    return m_y;
  }

  inline static int
  calculate_dimension (int window_dimension, int field_dimension)
  {
    return window_dimension / field_dimension;
  }

protected:
  int m_x, m_y;
  Color m_color;
};
