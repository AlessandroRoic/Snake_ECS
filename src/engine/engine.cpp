#include "engine.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "debuggers/logger.hpp"

bool Engine::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::logMessage("Failed to init SDL", true);
    return false;
  }

  const int imgFlags = IMG_INIT_PNG;
  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    Logger::logMessage("Failed to init IMG", true);
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    Logger::logMessage("Warning: Linear texture filtering not enabled!");
  }

  if (!windowManager.init(WINDOWED_MODE::WINDOW)) {
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

  return onInit();
}

void Engine::update() {
  timer.start();

  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
      return;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      inputManager.handleEvent(event);
      //TODO: pass to eventManager
      return;
    }
    eventManager.fire(&event);
  }
  if (!isStopped) {
    onUpdate(timer.deltaTime);
  }
}

void Engine::render() {
  // Clear screen before updating
  renderManager.clearScreen();

  // Check if rendering has stopped
  if (!isStopped) {
    onRender();
  } else {
    onRenderStop();
  }

  // Update screen and delta time
  renderManager.updateScreen();
  timer.updateDeltaTime();
}

void Engine::close() {
  // Close game & resources
  isRunning = false;
  onClose();

  // Then SDL resources
  renderManager.destroyRenderer();
  windowManager.destroyWindow();
  resourceManager.closeGlobalFont();
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Engine::setIsRunning(bool isRunning) {
  Engine::isRunning = isRunning;
}

void Engine::setIsStopped(bool isStopped) {
  Engine::isStopped = isStopped;
}

bool Engine::getIsRunning() const {
  return isRunning;
}

bool Engine::getIsStopped() const {
  return isStopped;
}
