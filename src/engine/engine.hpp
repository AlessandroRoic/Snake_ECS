#ifndef SNAKE_ECS_GAMEENGINE_H
#define SNAKE_ECS_GAMEENGINE_H

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
  const Event initEvent{INIT};
  Event updateEvent{UPDATE};
  Event updateStopEvent{UPDATE_STOP};
  const Event renderEvent{RENDER};
  const Event renderStopEvent{RENDER_STOP};
  const Event closeEvent{CLOSE};

 public:
  InputManager inputManager;
  WindowManager windowManager;
  EventManager eventManager;
  ResourceManager resourceManager;
  RenderManager renderManager;
  std::shared_ptr<EcsManager> ecsManager;
  int start();
  bool getIsRunning() const;
  void setIsRunning(bool isRunning);
  bool getIsStopped() const;
  void setIsStopped(bool isStopped);

 protected:
  bool init();
  void update();
  void render();
  void close();
};

#endif  // SNAKE_ECS_GAMEENGINE_H
