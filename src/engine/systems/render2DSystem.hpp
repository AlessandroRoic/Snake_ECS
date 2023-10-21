#ifndef SNAKE_ECS_RENDER2DSYSTEM_HPP
#define SNAKE_ECS_RENDER2DSYSTEM_HPP

#include <SDL_render.h>
#include <memory>
#include "../ecs/ECSManager.hpp"
#include "../ecs/system.hpp"

class Render2DSystem : public System {
  std::shared_ptr<EcsManager> ecsManager;

 public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager);
  void render(SDL_Renderer* renderer);
  void free();
};

#endif  //SNAKE_ECS_RENDER2DSYSTEM_HPP
