#ifndef SNAKE_ECS_TRANSFORM_HPP
#define SNAKE_ECS_TRANSFORM_HPP

#include "../math/vector2.hpp"

struct Transform2D {
  Vector2 position{0, 0};
  Vector2 velocity;
  Vector2 scale{1, 1};
};
#endif  //SNAKE_ECS_TRANSFORM_HPP
