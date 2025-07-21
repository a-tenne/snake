#include "SDL3/SDL_render.h"
#include <SDL3/SDL_video.h>
#include <string_view>
class Game
{
public:
  Game (std::string_view title, int width, int height);
  ~Game ();
  void run ();

private:
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  int m_width, m_height;
};
