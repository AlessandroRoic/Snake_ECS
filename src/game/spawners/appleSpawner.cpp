#include "appleSpawner.hpp"

#include <random>
#include "../components/collider.hpp"
#include "../components/sprite.hpp"
#include "../components/transform.hpp"

void onAppleCollision(Engine& engine, const EntityId self,
                      const EntityId other) {
  if (self != other) {
    engine.ecsManager->destroyEntity(self);
    AppleSpawner::spawn(engine);
  }
}

Vector2 generateRandomPoint(std::pair<int, int> windowDimensions) {
  const auto [maxX, maxY] = windowDimensions;
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution distributionX(0, maxX - 64);
  std::uniform_int_distribution distributionY(0, maxY - 64);

  return {static_cast<float>(distributionX(gen)),
          static_cast<float>(distributionY(gen))};
}

EntityId AppleSpawner::spawn(Engine& engine) {
  auto& ecsManager = engine.ecsManager;
  auto& renderManager = engine.renderManager;

  const EntityId entity = ecsManager->createEntity();

  const auto position =
      generateRandomPoint(engine.windowManager.getWindowDimensions());
  const SDLSprite texture = ResourceManager::loadSDL2Renderable(
      renderManager.getRenderer(), "./assets/apple.png", position);

  ecsManager->addComponent<Transform2D>(entity, Transform2D{position});
  ecsManager->addComponent<SDLSprite>(entity, texture);
  ecsManager->addComponent<Collider>(
      entity, {[&engine](const EntityId self, const EntityId other) {
        onAppleCollision(engine, self, other);
      }});
  return entity;
}
