/**
 * @file util.hpp
 * @author Alexsander d. S. Tenne
 * @brief Small header file containing various different utilities used across
 * all kinds of files.
 * @version 1.0.0
 * @date 02/08/2025
 */
#pragma once

#include <string>

/**
 * @brief Expands to a compiler-specific string literal representing the
 * current function signature.
 *
 * - GCC/Clang: uses __PRETTY_FUNCTION__
 * - MSVC: uses __FUNCSIG__
 * - Other: falls back to __FUNCTION__
 */
#if defined(__clang__) || defined(__GNUC__)
#define PRETTY_FN_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define PRETTY_FN_NAME __FUNCSIG__
#else
#define PRETTY_FN_NAME __FUNCTION__
#endif

/**
 * @brief Throws a runtime error with the latest SDL error message.
 * This function should be called when an SDL function fails and an error needs
 * to be propagated.
 *
 * @throws std::runtime_error With SDL error message.
 */
void sdl_exit_error ();

/**
 * @brief Calculates the size of each field cell based on window and field
 * dimensions.
 *
 * @param window_dimension The total size of the window (width or height).
 * @param field_dimension The number of cells in the respective dimension.
 * @return The size of one cell in pixels.
 * @throws std::logic_error if any parameter is <= 0.
 */
float calculate_dimension (int window_dimension, int field_dimension);

/**
 * @brief Resolves the path to the font asset, based on program startup path.
 * Will turn a Windows style path into a Unix style path.
 *
 * @param argc The argument count from main.
 * @param argv The argument vector from main.
 * @return Full path to the font file.
 * @throws std::invalid_argument if the path is malformed or unavailable.
 */
std::string resolve_font_path (int argc, char *const argv[]);
