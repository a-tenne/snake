/**
 * @file Game.hpp
 * @author Alexsander d. S. Tenne
 * @brief Declares the Game class managing the main Snake game loop, rendering,
 * input handling, and SDL initialization.
 * @version 1.0.0
 * @date 02/08/2025
 */
#pragma once

#include "GameField.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3/SDL.h>
#include <string_view>

/**
 * @class Game
 * @brief Controls the entire game lifecycle, rendering, and user input.
 *
 * This class initializes SDL and TTF, creates the window and renderer,
 * loads fonts, runs the main loop, processes events, and manages
 * game states (start, running, finished). It interacts with the GameField
 * for game logic such as snake movement and score tracking.
 */
class Game
{
public:
  /**
   * @brief Constructs and initializes the game.
   *
   * Initializes SDL and TTF subsystems, creates a window and renderer,
   * loads the font, and prepares the game field.
   *
   * @param title The window title.
   * @param width Window width in pixels (must be > 0).
   * @param height Window height in pixels (must be > 0).
   * @param sdl_flags Flags to initialize SDL (e.g., SDL_INIT_VIDEO).
   * @param window_flags Flags for window creation (e.g.,
   * SDL_WINDOW_RESIZABLE).
   * @param font_path Path to the TTF font file.
   * @param tps Ticks per second (game update rate, must be > 0).
   * @param fps Frames per second (rendering rate, must be > 0).
   *
   * @throws std::invalid_argument if any of width, height, tps, or fps <= 0.
   * @throws std::runtime_error via sdl_exit_error() on SDL or TTF
   * initialization failures.
   */
  Game (std::string_view title, int width, int height, SDL_InitFlags sdl_flags,
        SDL_WindowFlags window_flags, std::string_view font_path, int tps,
        int fps);

  /**
   * @brief Cleans up all allocated SDL and SDL_ttf resources.
   */
  ~Game ();

  /**
   * @brief Runs the main game loop, handling events, updating game logic,
   *        and rendering frames.
   *
   * This function blocks until the game is quit.
   */
  void run ();

private:
  /**
   * @brief Handles an incoming SDL event.
   * @param event The SDL event to process.
   * @throws std::runtime_error via sdl_exit_error() on SDL event failures.
   */
  void handle_event (SDL_Event &event);

  /**
   * @brief Renders the start screen.
   * @throws std::runtime_error via render_text_fields() on SDL render
   * failures.
   */
  void render_start ();

  /**
   * @brief Renders the game while running.
   * @throws std::runtime_error via sdl_exit_error() on SDL render failures.
   */
  void render_running ();

  /**
   * @brief Renders the game over (finish) screen.
   * @throws std::runtime_error via render_text_fields() on SDL render
   * failures.
   */
  void render_fini ();

  /**
   * @brief Renders the current high score on screen.
   * @return true if rendering succeeded, false otherwise.
   * @throws std::runtime_error via sdl_exit_error() on SDL surface or texture
   * creation failures.
   */
  bool render_high_score ();

  /**
   * @brief Helper function to render two text fields centered on screen.
   * @param field1 The first text line to render.
   * @param field2 The second text line to render.
   * @param show_high_score Whether to render the high score below.
   * @throws std::runtime_error via sdl_exit_error() on SDL render failures.
   */
  void render_text_fields (std::string_view field1, std::string_view field2,
                           bool show_high_score);

private:
  /// Custom deleter template for SDL resources, used with std::unique_ptr.
  template <typename T, void (*F) (T *)> struct SDL_deleter
  {
    void
    operator() (T *ptr)
    {
      if (ptr != nullptr)
        {
          F (ptr);
        }
    }
  };
  /// Template wrapper for using std::unique_ptr with SDL_deleter.
  template <typename T, void (*F) (T *)>
  using sdl_unique = std::unique_ptr<T, SDL_deleter<T, F>>;

  /**
   * @brief Unique pointer type managing SDL_Surface pointers with automatic
   * cleanup.
   *
   * Wraps an SDL_Surface pointer and calls SDL_DestroySurface automatically
   * when the pointer goes out of scope.
   */
  using surface_unique = sdl_unique<SDL_Surface, SDL_DestroySurface>;

  /**
   * @brief Unique pointer type managing SDL_Texture pointers with automatic
   * cleanup.
   *
   * Wraps an SDL_Texture pointer and calls SDL_DestroyTexture automatically
   * when the pointer goes out of scope.
   */
  using texture_unique = sdl_unique<SDL_Texture, SDL_DestroyTexture>;

private:
  /**
   * @enum GameState
   * @brief Represents the current state of the game.
   */
  enum class GameState
  {
    START,   ///< Before the game begins, waiting for input.
    RUNNING, ///< Game is in progress.
    FINI     ///< Game over screen, waiting for input to restart.
  } m_state;

  SDL_Window *m_window;     ///< Pointer to the SDL window.
  SDL_Renderer *m_renderer; ///< Pointer to the SDL renderer.
  TTF_Font *m_font;         ///< Loaded font for text rendering.
  GameField m_field;        ///< The game field containing snake and fruits.
  int m_width;              ///< Window width in pixels.
  int m_height;             ///< Window height in pixels.
  int m_high_score = 0;     ///< Highest score achieved in the session.
  const int m_tps;          ///< Target ticks per second (game logic updates).
  const int m_fps;          ///< Target frames per second (rendering).
  bool m_running = true;    ///< Flag to keep the main loop running.
  bool m_is_fullscreen = false; ///< Tracks fullscreen state.
  SDL_Time m_time;              ///< Time tracking for frame timing.
};
