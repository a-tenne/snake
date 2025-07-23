#include "GameField.hpp"
#include "Fruit.hpp"
#include "SDL3/SDL_render.h"
#include <algorithm>
#include <cstdlib>
#include <memory>

GameField::GameField (int height, int width)
    : m_height{ height }, m_width{ width }
{
}

void
GameField::spawn_fruit ()
{
  std::vector<coords> entity_coords;
  entity_coords.reserve (m_entities.size ());
  for (auto &entity : m_entities)
    {
      entity_coords.emplace_back (entity->get_x (), entity->get_y ());
    }
  auto collides = [entity_coords] (int x, int y) {
    return std::find (entity_coords.begin (), entity_coords.end (),
                      coords{ x, y })
           != entity_coords.end ();
  };
  int x, y;
  do
    {
      x = std::rand () % m_width;
      y = std::rand () % m_height;
    }
  while (collides (x, y));

  m_entities.push_back (std::make_unique<Fruit> (x, y));
}

void
GameField::render (SDL_Renderer &renderer, int window_height,
                   int window_width) const
{
  for (auto &entity : m_entities)
    {
      entity->render (renderer, window_height, window_width, m_height,
                      m_width);
    }
}
