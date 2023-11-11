#include "render2DSystem.hpp"
#include "../components/sprite.hpp"

Render2DSystem::Render2DSystem(const std::shared_ptr<EcsManager>& _ecsManager) {
  ecsManager = _ecsManager;
  Signature render2DSignature;
  render2DSignature.set(ecsManager->getComponentType<SDLSprite>());
  ecsManager->setSystemSignature<Render2DSystem>(render2DSignature);
}

void Render2DSystem::render(SDL_Renderer* renderer) const {
  for (auto const& entity : entities) {
    auto& [texture, rect] = ecsManager->getComponent<SDLSprite>(entity);
    SDL_RenderCopyF(renderer, texture, nullptr, &rect);
  }
}

void Render2DSystem::free() const {
  for (auto const& entity : entities) {
    auto& [texture, rect] = ecsManager->getComponent<SDLSprite>(entity);
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
}
