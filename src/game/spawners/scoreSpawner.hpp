#ifndef SCORESPAWNER_HPP
#define SCORESPAWNER_HPP

#include <engine.hpp>
#include "ecs/types.hpp"

class ScoreSpawner {
public:
  static EntityId spawn(Engine& engine);
};

#endif //SCORESPAWNER_HPP
