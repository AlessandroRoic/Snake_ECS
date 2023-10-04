#ifndef SNAKE_ECS_GAMEENGINE_H
#define SNAKE_ECS_GAMEENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <functional>
#include <iostream>
#include "deltaTimer.hpp"
#include "keyboardManager.hpp"

class Engine {
  DeltaTimer timer;

  // move to window manager
  const char* TITLE = "Pong";
  SDL_Window* window{};

  // move to resource manager
  TTF_Font* globalFont{};

  // move to event manager
  KeyboardManager keyboardManager;

 protected:
  bool init();
  void update();
  void render();
  void close();
  virtual bool onInit() = 0;
  virtual void onUpdate(float dt) = 0;
  virtual void onRender() = 0;
  virtual void onRenderStop() = 0;
  virtual void onClose() = 0;

  // Renderer manager
  SDL_Renderer* renderer{};

 public:
  // move to window manager
  static const int WINDOW_WIDTH = 1000;
  static const int WINDOW_HEIGHT = 600;

  // encapsulate
  bool isRunning = true;
  bool isStopped = false;
};

#endif  // SNAKE_ECS_GAMEENGINE_H
