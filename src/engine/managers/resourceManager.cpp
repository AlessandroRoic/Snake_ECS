#include "resourceManager.hpp"
#include <SDL_image.h>
#include "../debuggers/logger.hpp"

SDL2Renderable ResourceManager::loadSDL2Renderable(SDL_Renderer* renderer,
                                                   const char* path,
                                                   Vector2 position) {
  auto texture = IMG_LoadTexture(renderer, path);
  if (texture == nullptr) {
    Logger::logMessage("Texture not loaded", true);
  }
  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  auto rect = SDL_FRect{.x = position.x,
                        .y = position.y,
                        .w = static_cast<float>(w),
                        .h = static_cast<float>(h)};
  return {texture, rect};
}

TTF_Font* ResourceManager::getGlobalFont() const {
  return globalFont;
}

void ResourceManager::setGlobalFont(TTF_Font* font) {
  globalFont = font;
}

void ResourceManager::closeGlobalFont() {
  TTF_CloseFont(globalFont);
  globalFont = nullptr;
}
