#ifndef SNAKE_ECS_PLAYERCONTROLLER_HPP
#define SNAKE_ECS_PLAYERCONTROLLER_HPP

#include "engine.hpp"

class PlayerController {
 public:
  static EntityId spawn(const Engine& engine);
};

#endif  //SNAKE_ECS_PLAYERCONTROLLER_HPP
