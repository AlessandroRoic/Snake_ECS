#ifndef SNAKE_ECS_PHYSICS2DSYSTEM_HPP
#define SNAKE_ECS_PHYSICS2DSYSTEM_HPP

#include "../ecs/ECSManager.hpp"
#include "../ecs/system.hpp"

class Physics2DSystem : public System {
  std::shared_ptr<EcsManager> ecsManager;

 public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager);
  void update(float dt);
};

#endif  //SNAKE_ECS_PHYSICS2DSYSTEM_HPP
