#ifndef SNAKE_ECS_GAMEENGINE_H
#define SNAKE_ECS_GAMEENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <functional>
#include <iostream>
#include "deltaTimer.hpp"
#include "ecs/ECSManager.hpp"
#include "eventManager.hpp"
#include "inputManager.hpp"
#include "renderManager.hpp"
#include "resourceManager.hpp"
#include "windowManager.hpp"

class Engine {
  DeltaTimer timer;
  bool isRunning = true;
  bool isStopped = false;
  const Event initEvent{EventType::INIT};
  Event updateEvent{EventType::UPDATE};
  const Event renderEvent{EventType::RENDER};
  const Event renderStopEvent{EventType::RENDER_STOP};
  const Event closeEvent{EventType::CLOSE};

 public:
  InputManager inputManager;
  WindowManager windowManager;
  EventManager eventManager;
  ResourceManager resourceManager;
  RenderManager renderManager;
  std::shared_ptr<EcsManager> ecsManager;
  int start();

 protected:
  bool init();
  void update();
  void render();
  void close();
  bool getIsRunning() const;
  void setIsRunning(bool isRunning);
  bool getIsStopped() const;
  void setIsStopped(bool isStopped);
};

#endif  // SNAKE_ECS_GAMEENGINE_H
