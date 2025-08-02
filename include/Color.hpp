/**
 * @file Color.hpp
 * @author Alexsander d. S. Tenne
 * @brief Defines an RGBA color struct and provides commonly used color constants in a namespace.
 * @version 1.0.0
 * @date 02/08/2025
 */

#pragma once

#include "SDL3/SDL_stdinc.h"

/**
 * @brief Represents an RGBA color using 8-bit unsigned integers.
 */
struct Color
{
  Uint8 r; ///< Red component (0–255)
  Uint8 g; ///< Green component (0–255)
  Uint8 b; ///< Blue component (0–255)
  Uint8 a; ///< Alpha (opacity) component (0–255)
};

/**
 * @brief Contains predefined color constants used across the application.
 */
namespace colors {
  /// @brief Constant color value for red.
  constexpr Color RED{ 255, 0, 0, 1 };

  /// @brief Constant color value for green.
  constexpr Color GREEN{ 0, 255, 0, 1 };

  /// @brief Constant color value for black.
  constexpr Color BLACK{ 0, 0, 0, 1 };

  /// @brief Constant color value for yellow.
  constexpr Color YELLOW{ 255, 255, 0, 1 };

  /// @brief Constant color value for dark gray.
  constexpr Color GRAY{ 60, 60, 60, 1 };
}

