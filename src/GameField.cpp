#include "GameField.hpp"
#include "Fruit.hpp"
#include "Point.hpp"
#include "SDL3/SDL_render.h"
#include "SnakePart.hpp"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <unordered_map>

GameField::GameField (int height, int width, int num_fruits)
    : m_height{ height }, m_width{ width }, m_snake_alive{ false }, m_num_fruits{num_fruits}
{
  if(width <= 0) {
    throw std::invalid_argument(std::string("Invalid width passed to ") + __PRETTY_FUNCTION__ + ": " + std::to_string(width));
  }
  if(height <= 0) {
    throw std::invalid_argument(std::string("Invalid height passed to ") + __PRETTY_FUNCTION__ + ": " + std::to_string(height));
  }
  if(num_fruits <= 0) {
    throw std::invalid_argument(std::string("Invalid number of fruits passed to ") + __PRETTY_FUNCTION__ + ": " + std::to_string(num_fruits));
  }
}

void
GameField::spawn_fruit ()
{
  std::vector<const Point *> entity_coords;
  for (auto &entity : m_fruits)
    {
      entity_coords.push_back (&entity->get_point ());
    }
  const SnakePart &head = m_snake.get_head ();
  entity_coords.push_back (&head.get_point ());
  for (auto &part : m_snake.get_body ())
    {
      entity_coords.push_back (&part.get_point ());
    }
  auto collides = [entity_coords] (int x, int y) {
    return std::find_if (
               entity_coords.begin (), entity_coords.end (),
               [x, y] (const Point *p) { return p != nullptr && p->x == x && p->y == y; })
           != entity_coords.end ();
  };
  int x, y;
  do
    {
      x = std::rand () % m_width;
      y = std::rand () % m_height;
    }
  while (collides (x, y));

  m_fruits.push_back (std::make_unique<Fruit> (x, y));
}

void
GameField::render (SDL_Renderer &renderer, int window_height,
                   int window_width) const
{
  m_snake.get_head ().render (renderer, window_height, window_width, m_height,
                              m_width);
  for (auto &part : m_snake.get_body ())
    {
      part.render (renderer, window_height, window_width, m_height, m_width);
    }
  for (auto &entity : m_fruits)
    {
      entity->render (renderer, window_height, window_width, m_height,
                      m_width);
    }
}

void
GameField::update ()
{
  if (!m_snake_alive)
    {
      return;
    }
  m_snake.move ();
  if (wall_collides () || self_collides ())
    {
      m_snake_alive = false;
      return;
    }
  auto fruit_iter
      = std::find_if (m_fruits.begin (), m_fruits.end (), [this] (auto &f) {
          auto snake_head = m_snake.get_head ();
          return f->get_x () == snake_head.get_x ()
                 && f->get_y () == snake_head.get_y ();
        });
  if (fruit_iter != m_fruits.end ())
    {
      m_snake.eat_fruit ();
      m_fruits.erase (fruit_iter);
      spawn_fruit ();
    }
}

bool
GameField::wall_collides ()
{
  auto &head = m_snake.get_head ();
  return head.get_x () < 0 || head.get_x () >= m_width || head.get_y () < 0
         || head.get_y () >= m_height;
}

bool
GameField::self_collides ()
{
  auto &head = m_snake.get_head ();
  for (auto &part : m_snake.get_body ())
    {
      if (head.collides (part))
        return true;
    }
  return false;
}

void
GameField::change_snake_direction (Direction dir)
{
  static std::unordered_map<Direction, Direction> opposites
      = { { Direction::LEFT, Direction::RIGHT },
          { Direction::RIGHT, Direction::LEFT },
          { Direction::UP, Direction::DOWN },
          { Direction::DOWN, Direction::UP } };
  if (m_snake.get_body ().empty ())
    {
      m_snake.set_direction (dir);
      return;
    }
  auto it = opposites.find (dir);
  if (it != opposites.end ()
      && m_snake.get_head ().get_direction () != it->second)
    {
      m_snake.set_direction (dir);
    }
}

void GameField::init() {
  for(int _ : std::ranges::views::iota(0,m_num_fruits)) {
    spawn_fruit();
  }
  int x_snake = std::rand () % (m_width / 2) + m_width / 2;
  int y_snake = std::rand () % (m_height / 2) + m_height / 2;

  int dir_num = std::rand () % 4;
  Direction dir;
  switch (dir_num)
    {
    case 0:
      dir = Direction::UP;
      break;
    case 1:
      dir = Direction::DOWN;
      break;
    case 2:
      dir = Direction::LEFT;
      break;
    case 3:
      dir = Direction::RIGHT;
      break;
    default:
      throw std::logic_error("Invalid Direction in GameField constructor\n");
      break;
    }
  m_snake = Snake{ x_snake, y_snake, dir };
  m_snake_alive = true;
}
void
GameField::clear() {
  m_fruits.clear();
  m_snake = Snake();
  m_snake_alive = false;
}
