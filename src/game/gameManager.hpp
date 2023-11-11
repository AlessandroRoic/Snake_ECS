#ifndef SNAKE_ECS_GAMEMANAGER_HPP
#define SNAKE_ECS_GAMEMANAGER_HPP

#include "engine.hpp"
#include "gameState.hpp"
#include "systems/snakeSystem.hpp"

class GameManager {
  Engine engine;
  GameState gameState;
  std::shared_ptr<SnakeSystem> snakeSystem;

 public:
  int start();
  void onInit();
  void onUpdate(const Event* event) const;
  void onRender() const;
  void onRenderStop(const Event* event);
  void onClose() const;
};

#endif  //SNAKE_ECS_GAMEMANAGER_HPP
