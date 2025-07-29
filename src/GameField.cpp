#include "GameField.hpp"
#include "Fruit.hpp"
#include "Point.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SnakePart.hpp"
#include "util.hpp"
#include <algorithm>
#include <cstdlib>
#include <format>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <unordered_map>

GameField::GameField (int side_length, int num_fruits)
    : m_side_length{ side_length }, m_snake_alive{ false },
      m_num_fruits{ num_fruits }
{
  constexpr auto fn_name = pretty_fn_name ();
  if (side_length <= 0)
    {
      throw std::invalid_argument (std::format (
          "Invalid width passed to {}: {}\n", fn_name, side_length));
    }
  if (num_fruits <= 0)
    {
      throw std::invalid_argument (std::format (
          "Invalid number of fruits passed to {}: {}\n", fn_name, num_fruits));
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
    return std::find_if (entity_coords.begin (), entity_coords.end (),
                         [x, y] (const Point *p) {
                           return p != nullptr && p->x == x && p->y == y;
                         })
           != entity_coords.end ();
  };
  int x, y;
  do
    {
      x = std::rand () % m_side_length;
      y = std::rand () % m_side_length;
    }
  while (collides (x, y));

  m_fruits.push_back (std::make_unique<Fruit> (x, y));
}

void
GameField::render (SDL_Renderer &renderer, int window_height,
                   int window_width) const
{
  if(wall_collides()) {
    return;
  }
  SDL_FRect border;
  float diff = static_cast<float> (std::abs (window_height - window_width));
  border.x = window_width > window_height ? diff / 2 : 0;
  border.y = window_height > window_width ? diff / 2 : 0;
  border.w = window_width > window_height ? window_width - diff : window_width;
  border.h
      = window_height > window_width ? window_height - diff : window_height;
  float cell_width = calculate_dimension (border.w, m_side_length);
  float cell_height = calculate_dimension (border.h, m_side_length);
  float cell_size = std::min (cell_width, cell_height);

  std::vector<SDL_FRect> gray_rects;
  gray_rects.reserve ((m_side_length ^ 2) / 2);

  for (int i : std::ranges::views::iota (0, m_side_length))
    {
      for (int j : std::ranges::views::iota (0, m_side_length))
        {
          if (i % 2 != j % 2)
            {
              float h = cell_size;
              float w = cell_size;
              float x = i * cell_width + border.x;
              float y = j * cell_height + border.y;
              gray_rects.emplace_back (x, y, w, h);
            }
        }
    }
  SDL_SetRenderDrawColor (&renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
  SDL_RenderFillRects (&renderer, gray_rects.data (),
                       static_cast<int> (gray_rects.size ()));
  m_snake.get_head ().render (renderer, border, m_side_length);
  for (auto &part : m_snake.get_body ())
    {
      part.render (renderer, border, m_side_length);
    }
  for (auto &entity : m_fruits)
    {
      entity->render (renderer, border, m_side_length);
    }
  SDL_SetRenderDrawColor (&renderer, YELLOW.r, YELLOW.g, YELLOW.b, YELLOW.a);
  SDL_RenderRect (&renderer, &border);
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
GameField::wall_collides () const
{
  auto &head = m_snake.get_head ();
  return head.get_x () < 0 || head.get_x () >= m_side_length
         || head.get_y () < 0 || head.get_y () >= m_side_length;
}

bool
GameField::self_collides () const
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
  if (auto it = opposites.find (dir);
      it != opposites.end ()
      && m_snake.get_head ().get_direction () != it->second)
    {
      m_snake.set_direction (dir);
    }
}

void
GameField::init ()
{
  for (int _ : std::ranges::views::iota (0, m_num_fruits))
    {
      spawn_fruit ();
    }
  int x_snake = std::rand () % (m_side_length / 2) + m_side_length / 4;
  int y_snake = std::rand () % (m_side_length / 2) + m_side_length / 4;

  int dir_num = std::rand () % 4;
  Direction dir;

  constexpr auto fn_name = pretty_fn_name ();

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
      throw std::logic_error (
          std::format ("Invalid direction in {}\n", fn_name));
      break;
    }
  m_snake = Snake (x_snake, y_snake, dir);
  m_snake_alive = true;
}
void
GameField::clear ()
{
  m_fruits.clear ();
  m_snake = Snake ();
  m_snake_alive = false;
}
