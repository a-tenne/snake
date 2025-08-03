/**
 * @file SnakePart.hpp
 * @author Alexsander d. S. Tenne
 * @brief Declares the SnakePart class representing an individual segment of a
 * snake.
 * @version 1.0.0
 * @date 02/08/2025
 */

#pragma once

#include "Entity.hpp"

/**
 * @brief Represents an invalid position indicator for SnakeParts.
 */
constexpr int INVALID_POS = -1;

/**
 * @brief Enum class for movement directions of the snake.
 */
enum class Direction
{
  UP,     ///< Move upwards.
  DOWN,   ///< Move downwards.
  LEFT,   ///< Move left.
  RIGHT,  ///< Move right.
  INVALID ///< Invalid direction (used for error handling or uninitialized
          ///< state).
};

/**
 * @brief A class representing a part of the snake in the game.
 *
 * Inherits from the Entity class and includes movement direction state.
 */
class SnakePart : public Entity
{
public:
  /**
   * @brief Factory method for creating a SnakePart.
   * @param x The x coordinate of the part.
   * @param y The y coordinate of the part.
   * @param dir The initial movement direction of the part.
   * @return A SnakePart initialized with the given parameters.
   */
  static SnakePart create_part (int x, int y, Direction dir);

  /**
   * @brief Factory method for creating a SnakePart object with invalid state.
   * Trying to do anything useful with this without initializing modifying it
   * will most certainly lead to an error.
   * @return A SnakePart positioned at INVALID_POS and with INVALID direction.
   */
  static SnakePart create_invalid ();

  /**
   * @brief Retrieves the current direction of the part.
   * @return The direction the part is currently moving in.
   */
  Direction get_direction () const;

  /**
   * @brief Sets the movement direction of the part.
   * @param dir The direction to set.
   */
  void set_direction (Direction dir);

  /**
   * @brief Moves the part in its current direction by one unit.
   *
   * @throws std::logic_error if the current direction is invalid.
   */
  void move ();

private:
  /**
   * @brief Constructs a SnakePart at the given position and direction.
   * @param x The x coordinate.
   * @param y The y coordinate.
   * @param dir The initial direction.
   */
  SnakePart (int x, int y, Direction dir);

  Direction m_direction; ///< The direction the part is moving in.
};
