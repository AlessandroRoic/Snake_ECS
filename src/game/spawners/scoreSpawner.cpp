#include "scoreSpawner.hpp"
#include "../components/score.hpp"
#include "../components/sprite.hpp"

EntityId ScoreSpawner::spawn(Engine& engine) {
  auto& ecsManager = engine.ecsManager;

  const EntityId entity = ecsManager->createEntity();

  SDLSprite sprite{};
  ScoreComponent scoreComponent{};
  scoreComponent.textSurface =
      TTF_RenderText_Solid(engine.resourceManager.getGlobalFont(),
                           std::to_string(scoreComponent.score).c_str(),
                           engine.resourceManager.getTextColor());
  sprite.texture = SDL_CreateTextureFromSurface(
      engine.renderManager.getRenderer(), scoreComponent.textSurface);
  sprite.rect = {50, 50,
                 static_cast<float>(scoreComponent.textSurface->clip_rect.w + 50),
                 static_cast<float>(scoreComponent.textSurface->clip_rect.h + 50)};
  ecsManager->addComponent<SDLSprite>(entity, sprite);
  ecsManager->addComponent<ScoreComponent>(entity, scoreComponent);
  return entity;
}
