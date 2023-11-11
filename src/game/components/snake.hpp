#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL_rect.h>
#include <array>
#include <vector>
#include "../math/vector2.hpp"

enum SnakePart { HEAD, BODY, BODY_ANGLED, TAIL, TAIL_ANGLED };

struct SnakeUnit {
  SnakePart part;
  SDL_FRect rect;
  std::int16_t angle;
};

struct Snake {
  SDL_Texture* texture{};
  std::array<SDL_Rect, 5> partsRect;
  std::vector<SnakeUnit> composition;
  SDL_Scancode currentDirection;
  int currentPart = 0;
  float animateSpeed = 150;
  float lastUpdate = 0;
  std::pair<SDL_Scancode, Vector2> newDirection = {SDL_SCANCODE_UP,
                                                   Vector2{0, -1}};
};
#endif  // SNAKE_HPP
