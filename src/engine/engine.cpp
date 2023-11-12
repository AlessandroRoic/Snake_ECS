#include "engine.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "debuggers/logger.hpp"

int Engine::start() {
  if (!init()) {
    close();
    return 1;
  }

  while (isRunning) {
    update();
    render();
  }

  close();

  return 0;
}

bool Engine::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::logMessage("Failed to init SDL", true);
    return false;
  }

  if (constexpr int imgFlags = IMG_INIT_PNG;
      (IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    Logger::logMessage("Failed to init IMG", true);
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    Logger::logMessage("Warning: Linear texture filtering not enabled!");
  }

  if (!windowManager.init(WINDOW)) {
    return false;
  }

  if (!windowManager.getWindow()) {
    Logger::logMessage("Failed to load window", true);
    return false;
  }

  if (!renderManager.init(windowManager.getWindow())) {
    Logger::logMessage("Failed to load renderer", true);
    return false;
  }

  if (TTF_Init() != 0) {
    Logger::logMessage("Failed to init TTF", true);
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
    Logger::logMessage("Failed to init Mix Open Audio", true);
  }

  ecsManager = std::make_shared<EcsManager>();

  eventManager.fire(&initEvent);

  return true;
}

void Engine::update() {
  timer.start();

  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
      return;
    }
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      inputManager.handleEvent(event);
      //TODO: pass to eventManager
      return;
    }
    eventManager.fire(&event);
  }
  if (!isStopped) {
    updateEvent.data = timer.deltaTime;
    eventManager.fire(&updateEvent);
  } else {
    eventManager.fire(&updateStopEvent);
  }
}

void Engine::render() {
  // Clear screen before updating
  renderManager.clearScreen();

  // Check if rendering has stopped
  if (!isStopped) {
    eventManager.fire(&renderEvent);
  } else {
    eventManager.fire(&renderStopEvent);
  }

  // Update screen and delta time
  renderManager.updateScreen();
  timer.updateDeltaTime();
}

void Engine::close() {
  // Close game & resources
  isRunning = false;
  eventManager.fire(&closeEvent);

  // Then SDL resources
  eventManager.unsubscribeAll();
  renderManager.destroyRenderer();
  windowManager.destroyWindow();
  resourceManager.closeGlobalFont();
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Engine::setIsRunning(const bool isRunning) {
  Engine::isRunning = isRunning;
}

void Engine::setIsStopped(const bool isStopped) {
  Engine::isStopped = isStopped;
}

bool Engine::getIsRunning() const {
  return isRunning;
}

bool Engine::getIsStopped() const {
  return isStopped;
}
