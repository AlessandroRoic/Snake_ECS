#ifndef SNAKE_ECS_PHYSICS2DSYSTEM_HPP
#define SNAKE_ECS_PHYSICS2DSYSTEM_HPP

#include "../ecs/ecsPlaceholder.hpp"
#include "../ecs/system.hpp"

class Physics2DSystem : public System {
 public:
  static std::shared_ptr<Physics2DSystem> init();
  void update(float dt);
};

#endif  //SNAKE_ECS_PHYSICS2DSYSTEM_HPP
