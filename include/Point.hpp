/**
 * @file Point.hpp
 * @author Alexsander d. S. Tenne
 * @brief Defines a simple 2D point structure with equality comparison.
 * @version 1.0.0
 * @date 02/08/2025
 */
#pragma once

/**
 * @brief Represents a 2D point with integer coordinates.
 *
 * Provides an equality operator to compare two points based on their coordinates.
 */
struct Point
{
  int x; ///< X coordinate.
  int y; ///< Y coordinate.

  /**
   * @brief Equality operator to compare two points.
   * @param other The point to compare with.
   * @return true if both x and y coordinates match, false otherwise.
   */
  bool operator== (const Point &other) const
  {
    return x == other.x && y == other.y;
  }
};
