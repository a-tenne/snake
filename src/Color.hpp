#pragma once

#include "SDL3/SDL_stdinc.h"

struct Color {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
};

constexpr Color RED{255,0,0,1};
constexpr Color GREEN{0,255,0,1};
constexpr Color BLACK{0,0,0,1};
constexpr Color YELLOW{255,255,0,1};
constexpr Color GRAY{60,60,60,1};
