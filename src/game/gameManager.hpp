#ifndef SNAKE_ECS_GAMEMANAGER_HPP
#define SNAKE_ECS_GAMEMANAGER_HPP

#include "engine.hpp"
#include "systems/snakeSystem.hpp"

class GameManager {
  Engine engine;
  std::shared_ptr<SnakeSystem> snakeSystem;
  EntityId snake{};

 public:
  int start();
  void onInit();
  void onUpdate(const Event* event) const;
  void onRender() const;
  void onRenderStop() const;
  void onClose() const;
  void onGameEnd();
};

#endif  //SNAKE_ECS_GAMEMANAGER_HPP
