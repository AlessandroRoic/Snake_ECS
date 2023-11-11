#ifndef SNAKE_ECS_SNAKESYSTEM_HPP
#define SNAKE_ECS_SNAKESYSTEM_HPP

#include <SDL_render.h>
#include "ecs/ECSManager.hpp"
#include "ecs/system.hpp"
#include <SDL_scancode.h>
#include <unordered_set>

class SnakeSystem: public System {
  std::shared_ptr<EcsManager> ecsManager;

 public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager);
  void update(float dt, const std::unordered_set<SDL_Scancode>& pressedKeys) const;
  void render(SDL_Renderer* renderer) const;
  void free() const;
};

#endif  //SNAKE_ECS_SNAKESYSTEM_HPP
