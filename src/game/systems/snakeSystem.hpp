#ifndef SNAKE_ECS_SNAKESYSTEM_HPP
#define SNAKE_ECS_SNAKESYSTEM_HPP

#include <SDL_render.h>
#include <SDL_scancode.h>
#include <eventManager.hpp>
#include <unordered_set>
#include "ecs/ECSManager.hpp"
#include "ecs/system.hpp"

class SnakeSystem : public System {
  std::shared_ptr<EcsManager> ecsManager;
  EventManager* eventManager{};
  int screenWidth{};
  int screenHeight{};

 public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager,
            EventManager* _eventManager, int _screenWidth, int _screenHeight);
  void update(float dt,
              const std::unordered_set<SDL_Scancode>& pressedKeys) const;
  void render(SDL_Renderer* renderer) const;
  void free() const;
};

#endif  //SNAKE_ECS_SNAKESYSTEM_HPP
