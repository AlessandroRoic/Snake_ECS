#include "resourceManager.hpp"
#include <SDL_image.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../debuggers/logger.hpp"

SDLSprite ResourceManager::loadSDL2Renderable(SDL_Renderer* renderer,
                                                   const char* path,
                                              const Vector2 position) {
  const auto texture = loadSDLTexture(renderer, path);
  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  const auto rect = SDL_FRect{.x = position.x,
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

SDL_Texture* ResourceManager::loadSDLTexture(SDL_Renderer* renderer,
                                             const char* path) {
  const auto texture = IMG_LoadTexture(renderer, path);
  if (texture == nullptr) {
    Logger::logMessage("Texture not loaded", true);
  }
  return texture;
}

nlohmann::basic_json<> ResourceManager::loadJSON(const char* path) {
  std::ifstream i(path);
  nlohmann::json j;
  i >> j;
  return j;
}
