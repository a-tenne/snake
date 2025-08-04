/**
 * @file Snake.hpp
 * @author Alexsander d. S. Tenne
 * @brief Defines the Snake class representing the snake in the game.
 * @version 1.1.0
 * @date 02/08/2025
 */

#pragma once

#include "SnakePart.hpp"
#include <vector>

/**
 * @brief Class representing the snake in the Snake game.
 *
 * The snake is composed of a head and a vector of body parts (tail).
 * It moves in discrete steps and grows when it eats a fruit.
 */
class Snake
{
public:
  /**
   * @brief Factory method for creating a valid Snake instance.
   * @param x_head X coordinate of the snake's head.
   * @param y_head Y coordinate of the snake's head.
   * @param dir Initial direction of the snake.
   * @return A fully initialized Snake instance.
   */
  static Snake create_snake (int x_head, int y_head, Direction dir);

  /**
   * @brief Factory method for creating a Snake object with invalid state.
   * Trying to do anything useful with this without initializing modifying it
   * will most certainly lead to an error.
   * @return A Snake initialized in an invalid state.
   */
  static Snake create_invalid ();

  /**
   * @brief Sets the direction the snake's head should move in.
   * @param dir New movement direction.
   */
  void set_direction (Direction dir);

  /**
   * @brief Returns a const reference to the snake's head.
   * @return const reference to the SnakePart representing the head.
   */
  const SnakePart &get_head () const;

  /**
   * @brief Returns a const reference to the snake's body.
   * @return const reference to the vector of SnakePart representing the body.
   */
  const std::vector<SnakePart> &get_body () const;

  /**
   * @brief Moves the snake one step forward.
   *
   * Updates all parts of the snake to simulate movement.
   * @throws std::logic_error if logic fails internally (in
   * `SnakePart::move()`).
   */
  void move ();

  /**
   * @brief Grows the snake by adding one new part at the tail.
   *
   * Uses `m_last_pos` to determine the correct position and direction of the
   * new segment.
   * @throws std::logic_error if called before any movement occurs.
   */
  void eat_fruit ();

  /**
   * @brief Sets the renderer color to a certain value.
   *
   * @param renderer The target renderer.
   * @throws std::runtime_error via sdl_exit_error() if setting the color
   * fails.
   */
  static void set_color (SDL_Renderer &renderer);

private:
  /**
   * @brief Constructs a Snake with a head position and initial direction.
   * @param x_head X coordinate of the head.
   * @param y_head Y coordinate of the head.
   * @param dir Initial direction of movement.
   */
  Snake (int x_head, int y_head, Direction dir);

  SnakePart m_head;              ///< The head of the snake.
  std::vector<SnakePart> m_body; ///< The body parts of the snake.
  SnakePart
      m_last_pos; ///< Used to remember the tail's last position for growing.
};
