/**
 * @file Fruit.hpp
 * @author Alexsander d. S. Tenne
 * @brief Declares the Fruit class, a specialized Entity representing a collectible item in the game.
 * @version 1.0.0
 * @date 02/08/2025
 */
#pragma once
#include "Entity.hpp"

/**
 * @brief Represents a fruit entity that can be collected by the player.
 * Inherits from Entity and uses a predefined color to distinguish fruits from other game elements.
 */
class Fruit : public Entity
{
public:
  /**
   * @brief Constructs a Fruit at the specified grid position.
   * @param x The X coordinate on the grid.
   * @param y The Y coordinate on the grid.
   */
  Fruit (int x, int y);
};

