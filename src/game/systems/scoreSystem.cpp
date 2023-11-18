#include "scoreSystem.hpp"
#include <SDL_ttf.h>
#include "../components/score.hpp"
#include "../components/sprite.hpp"

void ScoreSystem::init(const std::shared_ptr<EcsManager>& _ecsManager) {
  ecsManager = _ecsManager;
  Signature collisionSignature;
  collisionSignature.set(ecsManager->getComponentType<ScoreComponent>());
  ecsManager->setSystemSignature<ScoreSystem>(collisionSignature);
}

void ScoreSystem::render(SDL_Renderer* renderer, TTF_Font* font,
                         const SDL_Color color) const {
  const auto& entity = *entities.begin();
  auto [texture, rect] = ecsManager->getComponent<SDLSprite>(entity);
  auto [textSurface, score] = ecsManager->getComponent<ScoreComponent>(entity);
  textSurface =
      TTF_RenderText_Solid(font, std::to_string(score).c_str(), color);
  texture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}

void ScoreSystem::free() const {
  const auto& entity = *entities.begin();
  const SDLSprite sprite = ecsManager->getComponent<SDLSprite>(entity);
  ScoreComponent scoreComponent =
      ecsManager->getComponent<ScoreComponent>(entity);
  SDL_DestroyTexture(sprite.texture);
  SDL_FreeSurface(scoreComponent.textSurface);
}
