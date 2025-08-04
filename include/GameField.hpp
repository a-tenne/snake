/**
 * @file GameField.hpp
 * @author Alexsander d. S. Tenne
 * @brief Defines the GameField class which manages the game field's state,
 * logic, and rendering.
 * @version 1.1.0
 * @date 02/08/2025
 */
#pragma once

#include "Fruit.hpp"
#include "SDL3/SDL_render.h"
#include "Snake.hpp"
#include <unordered_map>
#include <vector>

/**
 * @brief Class responsible for the game field's logic, updating state, and
 * rendering.
 *
 * Manages the snake, fruits, collision detection, and rendering on screen.
 */
class GameField
{
public:
  /**
   * @brief Constructs the game field.
   * @param side_length The number of cells on one side of the square field.
   * @param num_fruits Number of fruits to spawn initially.
   * @throws std::invalid_argument If parameters are invalid or there's not
   * enough space for fruits.
   */
  GameField (int side_length, int num_fruits);

  /**
   * @brief Updates the game state by moving the snake, checking collisions,
   * and handling fruit consumption.
   */
  void update ();

  /**
   * @brief Renders the game field including snake, fruits, and background.
   * @param renderer SDL_Renderer used for drawing.
   * @param window_height Height of the window in pixels.
   * @param window_width Width of the window in pixels.
   * @throws std::logic_error If an entity is positioned outside the valid
   * range.
   * @throws std::runtime_error If SDL rendering fails.
   */
  void render (SDL_Renderer &renderer, int window_height, int window_width);

  /**
   * @brief Changes the contents of the value of the snake direction buffer if
   * valid.
   * @param dir New direction to set for the buffer.
   * @throws std::logic_error If snake state or direction change is invalid.
   */
  void change_snake_direction (Direction dir);

  /**
   * @brief Initializes the game by spawning fruits and creating a new snake.
   * @throws std::logic_error If value generated is not a valid direction,
   * which should never happen.
   */
  void init ();

  /**
   * @brief Clears the game field, removing all fruits and resetting snake
   * state.
   */
  void clear ();

  /**
   * @brief Checks if the snake is alive.
   * @return True if the snake is alive, false otherwise.
   */
  bool is_snake_alive () const;

  /**
   * @brief Gets the current score, defined as the snake's body length.
   * @return The number of segments in the snake's body.
   */
  int get_score () const;

private:
  /**
   * @brief Checks if the snake has collided with the walls of the game field.
   * @return True if collision with walls occurred, false otherwise.
   */
  bool wall_collides () const;

  /**
   * @brief Checks if the snake has collided with itself.
   * @return True if self-collision occurred, false otherwise.
   */
  bool self_collides () const;

  /**
   * @brief Spawns a new fruit at a random unoccupied position.
   */
  void spawn_fruit ();

private:
  std::vector<Fruit> m_fruits; ///< Container for fruits on the field.
  Snake m_snake;               ///< The snake instance.
  const int m_side_length;     ///< Number of cells per side.
  const int m_num_fruits;      ///< Number of fruits to spawn.
  bool m_snake_alive = false;  ///< Whether the snake is alive.
  struct
  {
    int width = 0;  ///< The window's old width.
    int height = 0; ///< The window's old height.
  } m_last_window;  ///< Container for old window data, used to avoid
                    ///< unneccessary calculations.
  SDL_FRect m_border
      = { 0 }; ///< Used for storing the border of the game field.
  std::vector<SDL_FRect> m_gray_rects; ///< Used for storing the gray squares
                                       ///< that get rendered on the field.
  Direction m_dir_buffer
      = Direction::INVALID; ///< Buffer for direction changes.
  std::unordered_map<Direction, Direction> m_opposites{
    { Direction::LEFT, Direction::RIGHT },
    { Direction::RIGHT, Direction::LEFT },
    { Direction::UP, Direction::DOWN },
    { Direction::DOWN, Direction::UP }
  }; ///< Pairs of directions that are opposite to each other.
};
