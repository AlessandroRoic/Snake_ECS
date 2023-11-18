#ifndef SNAKE_ECS_GAMEMANAGER_HPP
#define SNAKE_ECS_GAMEMANAGER_HPP

#include "systems/collisionSystem.hpp"
#include "components/gameOverScreen.hpp"
#include "engine.hpp"
#include "systems/render2DSystem.hpp"
#include "systems/snakeSystem.hpp"

class GameManager {
  Engine engine;
  std::shared_ptr<SnakeSystem> snakeSystem;
  std::shared_ptr<Render2DSystem> renderSystem;
  std::shared_ptr<CollisionSystem> collisionSystem;
  EntityId snake{};
  SDL_TimerID gameOverTimerID{0};
  GameOverScreen gameOverScreen;

 public:
  int start();
  void onInit();
  void onUpdate(const Event* event);
  void onRender() const;
  void onRenderStop();
  void onClose() const;
  void onGameEnd();
};

#endif  //SNAKE_ECS_GAMEMANAGER_HPP
