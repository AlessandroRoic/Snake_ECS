#ifndef SNAKE_ECS_GAMEENGINE_H
#define SNAKE_ECS_GAMEENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <functional>
#include <iostream>
#include "deltaTimer.hpp"
#include "eventManager.hpp"
#include "inputManager.hpp"
#include "resourceManager.hpp"
#include "windowManager.hpp"

class Engine {
  DeltaTimer timer;
  bool isRunning = true;
  bool isStopped = false;

 protected:
  InputManager inputManager;
  WindowManager windowManager;
  EventManager eventManager;
  ResourceManager resourceManager;
  SDL_Renderer* renderer{};
  bool init();
  void update();
  void render();
  void close();
  virtual bool onInit() = 0;
  virtual void onUpdate(float dt) = 0;
  virtual void onRender() = 0;
  virtual void onRenderStop() = 0;
  virtual void onClose() = 0;
  bool getIsRunning() const;
  void setIsRunning(bool isRunning);
  bool getIsStopped() const;
  void setIsStopped(bool isStopped);
};

#endif  // SNAKE_ECS_GAMEENGINE_H
