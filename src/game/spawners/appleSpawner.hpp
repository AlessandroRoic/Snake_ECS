#ifndef APPLESPAWNER_HPP
#define APPLESPAWNER_HPP

#include <engine.hpp>
#include "ecs/types.hpp"

class AppleSpawner {
 public:
  static EntityId spawn(Engine& engine);
};

#endif  //APPLESPAWNER_HPP
