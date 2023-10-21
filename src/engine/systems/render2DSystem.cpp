#include "render2DSystem.hpp"
#include "../components/renderable.hpp"

void Render2DSystem::render(SDL_Renderer* renderer) {
  for (auto const& entity : entities) {
    auto& sdl2Renderable = ecsManager->getComponent<SDL2Renderable>(entity);
    SDL_RenderCopyF(renderer, sdl2Renderable.texture, nullptr,
                    &sdl2Renderable.rect);
  }
}

void Render2DSystem::free() {
  for (auto const& entity : entities) {
    auto& sdl2Renderable = ecsManager->getComponent<SDL2Renderable>(entity);
    SDL_DestroyTexture(sdl2Renderable.texture);
    sdl2Renderable.texture = nullptr;
  }
}

void Render2DSystem::init(const std::shared_ptr<EcsManager>& _ecsManager) {
  ecsManager = _ecsManager;
  Signature render2DSignature;
  render2DSignature.set(ecsManager->getComponentType<SDL2Renderable>());
  ecsManager->setSystemSignature<Render2DSystem>(render2DSignature);
}
