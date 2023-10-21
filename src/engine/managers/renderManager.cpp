#include "renderManager.hpp"

bool RenderManager::init(SDL_Window* window) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  return renderer != nullptr;
}

SDL_Renderer* RenderManager::getRenderer() const {
  return renderer;
}

void RenderManager::updateScreen() {
  SDL_RenderPresent(renderer);
}

void RenderManager::clearScreen() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void RenderManager::destroyRenderer() {
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
}
