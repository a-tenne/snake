#pragma once
#include "Entity.hpp"
class Fruit : public Entity
{
public:
  Fruit (int window_height, int window_width);
  ~Fruit () = default;
  void render (SDL_Renderer &renderer, int window_height, int window_width,
               int field_height, int field_width) const;
};
