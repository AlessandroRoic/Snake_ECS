#ifndef SNAKE_ECS_PHYSICS2DSYSTEM_HPP
#define SNAKE_ECS_PHYSICS2DSYSTEM_HPP

#include "../ecs/system.hpp"

class Physics2DSystem : public System {
 public:
  void update(float dt);
};

#endif  //SNAKE_ECS_PHYSICS2DSYSTEM_HPP
