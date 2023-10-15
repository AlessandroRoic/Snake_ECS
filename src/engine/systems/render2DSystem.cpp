#include "render2DSystem.hpp"
#include "../components/renderable.hpp"
#include "../ecs/ecsPlaceholder.hpp"

void Render2DSystem::render(SDL_Renderer *renderer) {
  for (auto const& entity : entities) {
    auto& sdl2Renderable =
        EcsPlaceholder::getInstance().getComponent<SDL2Renderable>(entity);
    SDL_RenderCopyF(renderer, sdl2Renderable.texture, nullptr,
                    &sdl2Renderable.rect);
  }
}

void Render2DSystem::free() {
  for (auto const& entity : entities) {
    auto& sdl2Renderable =
        EcsPlaceholder::getInstance().getComponent<SDL2Renderable>(entity);
    SDL_DestroyTexture(sdl2Renderable.texture);
    sdl2Renderable.texture = nullptr;
  }
}

std::shared_ptr<Render2DSystem> Render2DSystem::init() {
  auto &ecsPlaceholder = EcsPlaceholder::getInstance();
  auto system = ecsPlaceholder.registerSystem<Render2DSystem>();
  Signature render2DSignature;
  render2DSignature.set(ecsPlaceholder.getComponentType<SDL2Renderable>());
  ecsPlaceholder.setSystemSignature<Render2DSystem>(render2DSignature);
  return system;
}
