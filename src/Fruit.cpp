#include "Fruit.hpp"
#include "Color.hpp"
#include "util.hpp"

Fruit::Fruit (int x, int y) : Entity{ x, y } {}

void
Fruit::set_color (SDL_Renderer &renderer)
{
  using colors::RED;
  if (!SDL_SetRenderDrawColor (&renderer, RED.r, RED.g, RED.b, RED.a))
      [[unlikely]]
    {
      sdl_exit_error ();
    }
}
