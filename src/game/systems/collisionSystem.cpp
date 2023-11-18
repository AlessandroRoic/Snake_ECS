#include "collisionSystem.hpp"
#include "../components/collider.hpp"
#include "../components/score.hpp"
#include "../components/snake.hpp"
#include "../components/sprite.hpp"

void CollisionSystem::init(const std::shared_ptr<EcsManager>& _ecsManager) {
  ecsManager = _ecsManager;
  Signature collisionSignature;
  collisionSignature.set(ecsManager->getComponentType<Collider>());
  ecsManager->setSystemSignature<CollisionSystem>(collisionSignature);
}

void CollisionSystem::update(const EntityId& snakeEntityId, const EntityId& scoreEntityId) {
  Snake snake = ecsManager->getComponent<Snake>(snakeEntityId);
  SDL_FRect head = snake.composition.at(0).rect;
  for (int i = 3; i < snake.composition.size(); i++) {
    const auto& part = snake.composition.at(i);
    if (SDL_HasIntersectionF(&head, &part.rect)) {
      auto& scoreComponent = ecsManager->getComponent<ScoreComponent>(scoreEntityId);
      scoreComponent.score = 0;
      ecsManager->getComponent<Collider>(snakeEntityId)
          .onCollide(snakeEntityId, snakeEntityId);
    }
  }
  for (auto entity : entities) {
    if (entity == snakeEntityId)
      continue;
    SDLSprite apple = ecsManager->getComponent<SDLSprite>(entity);
    if (SDL_HasIntersectionF(&head, &apple.rect)) {
      collidedEntities.insert({snakeEntityId, entity});
    }
  }
  for (auto [snakeEntityId, entity] : collidedEntities) {
    ecsManager->getComponent<Collider>(snakeEntityId)
        .onCollide(snakeEntityId, entity);
    ecsManager->getComponent<Collider>(entity).onCollide(entity, snakeEntityId);
    auto& scoreComponent = ecsManager->getComponent<ScoreComponent>(scoreEntityId);
    scoreComponent.score+= 10;
  }
  collidedEntities = {};
}
