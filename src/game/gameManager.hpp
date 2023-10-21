#ifndef SNAKE_ECS_GAMEMANAGER_HPP
#define SNAKE_ECS_GAMEMANAGER_HPP
#include "engineStarter.hpp"
#include "gameState.hpp"

class GameManager {
  EngineStarter engine;
  GameState gameState;

 public:
  int start();
};
#endif  //SNAKE_ECS_GAMEMANAGER_HPP
