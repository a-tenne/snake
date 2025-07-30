#pragma once

#include "Fruit.hpp"
#include "SDL3/SDL_render.h"
#include "Snake.hpp"
#include <memory>

class GameField
{
public:
  GameField (int side_length, int num_fruits);
  void update ();
  void render (SDL_Renderer &renderer, int window_height,
               int window_width) const;
  void change_snake_direction (Direction dir);
  void init ();
  void clear ();

  inline bool
  is_snake_alive () const
  {
    return m_snake_alive;
  }

  inline int
  get_score () const
  {
    return static_cast<int> (m_snake.get_body ().size ());
  }

private:
  bool wall_collides () const;
  bool self_collides () const;
  void spawn_fruit ();

private:
  std::vector<std::unique_ptr<Fruit>> m_fruits;
  Snake m_snake;
  int m_side_length, m_num_fruits;
  bool m_snake_alive;
};
