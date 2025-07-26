#pragma once

#include "Fruit.hpp"
#include "SDL3/SDL_render.h"
#include "Snake.hpp"
#include <memory>

class GameField
{
public:
  GameField (int height, int width);
  void spawn_fruit ();
  void update ();
  void render (SDL_Renderer &renderer, int window_height,
               int window_width) const;
  void
  change_snake_direction (Direction dir);

  inline bool
  is_snake_alive () const
  {
    return m_snake_alive;
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

  bool wall_collides ();
  bool self_collides();

private:
  std::vector<std::unique_ptr<Fruit>> m_fruits;
  Snake m_snake;
  int m_height, m_width;
  bool m_snake_alive;
};
