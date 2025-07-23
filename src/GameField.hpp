#pragma once

#include "Entity.hpp"
#include "SDL3/SDL_render.h"
#include <memory>

class GameField
{
public:
  GameField (int height, int width);
  void spawn_fruit ();
  void render (SDL_Renderer &renderer, int window_height,
               int window_width) const;
  inline void
  clear ()
  {
    m_entities.clear ();
  }

private:
  struct coords
  {
    int x;
    int y;
    bool
    operator== (const coords &other) const
    {
      return x == other.x && y == other.y;
    }
  };

private:
  std::vector<std::unique_ptr<Entity>> m_entities;
  int m_height, m_width;
};
