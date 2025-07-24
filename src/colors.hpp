#pragma once

struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

constexpr Color RED{255,0,0,1};
constexpr Color GREEN{0,255,0,1};
constexpr Color BLACK{0,0,0,1};

