#ifndef SNAKE_ECS_PLAYERSPAWNER_HPP
#define SNAKE_ECS_PLAYERSPAWNER_HPP

#include "engine.hpp"

class PlayerSpawner {
 public:
  static EntityId spawn(Engine& engine);
};

#endif  //SNAKE_ECS_PLAYERSPAWNER_HPP
