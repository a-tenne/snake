/**
 * @file config.hpp
 * @author Alexsander d. S. Tenne
 * @brief Defines configuration constants for the Snake game application.
 * @version 1.0.0
 * @date 02/08/2025
 */
#pragma once
#include <string_view>
#define SDL_MAIN_HANDLED
#include "SDL3/SDL_init.h"

/**
 * @brief Contains compile-time configuration values for the application.
 */
namespace config
{
/// @brief Window name.
constexpr std::string_view NAME = "Snake";

/// @brief Default width of the game window in pixels.
constexpr int WINDOW_WIDTH = 1000;

/// @brief Default height of the game window in pixels.
constexpr int WINDOW_HEIGHT = 700;

/// @brief SDL initialization flags (e.g., video subsystem).
constexpr SDL_InitFlags SDL_FLAGS = SDL_INIT_VIDEO;

/// @brief SDL window creation flags (e.g., resizable window).
constexpr SDL_WindowFlags WINDOW_FLAGS = SDL_WINDOW_RESIZABLE;

/// @brief Target frame rate of the game (frames per second).
constexpr int FRAME_RATE = 60;

/// @brief Game logic update frequency (ticks per second).
constexpr int TICKS_PER_SECOND = 7;

/// @brief The number of horizontal and vertical tiles on the game board.
constexpr int SIDE_LENGTH = 25;

/// @brief Number of fruit entities present on the game board simultaneously.
constexpr int NUM_FRUITS = 4;

/// @brief Font size used for rendering text.
constexpr float FONT_SIZE = 60;
}

#undef SDL_MAIN_HANDLED
