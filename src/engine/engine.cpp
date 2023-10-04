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

  window =
      SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    Logger::logMessage("Failed to load window", true);
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
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
    // TODO: pass event to event manage
    if (event.type == SDL_QUIT) {
      isRunning = false;
      return;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      keyboardManager.handleEvent(event);
    }
  }
  if (!isStopped) {
    onUpdate(timer.deltaTime);
  }
}

void Engine::render() {
  // Clear screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  if (!isStopped) {
    onRender();
  } else {
    onRenderStop();
  }

  // Update screen
  SDL_RenderPresent(renderer);
  timer.updateDeltaTime();
}

void Engine::close() {
  // Close game & resources
  isRunning = false;
  onClose();
  // Then SDL resources
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(globalFont);
  renderer = nullptr;
  window = nullptr;
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
