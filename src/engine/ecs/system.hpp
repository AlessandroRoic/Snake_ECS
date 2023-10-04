#ifndef SNAKE_ECS_SYSTEM_HPP
#define SNAKE_ECS_SYSTEM_HPP

#include <set>
#include "types.hpp"

class System {
 public:
  std::set<EntityId> entities;
};

#endif  //SNAKE_ECS_SYSTEM_HPP
