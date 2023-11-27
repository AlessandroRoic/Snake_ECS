#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_scancode.h>
#include <array>
#include <vector>

enum SnakePart { HEAD, BODY, BODY_ANGLED, TAIL, TAIL_ANGLED };

enum AXIS { VERTICAL, HORIZONTAL };

struct SnakeUnit {
  SnakePart part{};
  SDL_FRect positionRect{};
  std::int16_t angle{};
  SDL_Scancode currentDirection{SDL_SCANCODE_UP};
  SDL_Scancode newDirection{SDL_SCANCODE_UP};
  bool isAngled = false;
  float animationCounter = -1;
};

struct Snake {
  SDL_Texture* texture{};
  std::array<SDL_Rect, 5> partsClip;
  std::vector<SnakeUnit> composition;
  float speed = 0.3;
};

#endif  // SNAKE_HPP
