/**
 * @file Entity.hpp
 * @author Alexsander d. S. Tenne
 * @brief Declares the Entity class representing a renderable, position-aware
 * object.
 * @version 1.0.0
 * @date 02/08/2025
 */
#pragma once

#include "Color.hpp"
#include "Point.hpp"
#include "SDL3/SDL_render.h"

/**
 * @brief Represents a basic 2D entity with a position and color that can be
 * rendered.
 */
class Entity
{
public:
  /**
   * @brief Constructs an entity at the given (x, y) coordinate with a
   * specified color.
   * @param x The horizontal coordinate on the grid.
   * @param y The vertical coordinate on the grid.
   * @param color The color of the entity.
   */
  Entity (int x, int y, Color color);

  /**
   * @brief Renders the entity to the provided SDL renderer.
   *
   * @param renderer The SDL renderer to draw to.
   * @param border The drawable area offset and dimensions.
   * @param side_length The number of cells per row/column in the grid.
   *
   * @throws std::logic_error if the entity is positioned outside the valid
   * range or if the border parameter's height does not equal its width.
   * @throws std::runtime_error if SDL rendering fails.
   */
  void render (SDL_Renderer &renderer, const SDL_FRect &border,
               int side_length) const;

  /**
   * @brief Checks for collision (same position) with another entity.
   * @param other The other entity to compare against.
   * @return true if both entities occupy the same coordinates.
   */
  bool collides (const Entity &other) const;

  /// @brief Gets the x coordinate of the entity.
  int get_x () const;

  /// @brief Gets the y coordinate of the entity.
  int get_y () const;

  /// @brief Returns a const reference to the entity's position.
  const Point &get_point () const;

  /// @brief Sets the x coordinate of the entity.
  void set_x (int x);

  /// @brief Sets the y coordinate of the entity.
  void set_y (int y);

protected:
  Point m_point; ///< The entity's 2D grid position.
  Color m_color; ///< The entity's render color.
};
