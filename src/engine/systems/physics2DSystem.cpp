#include "physics2DSystem.hpp"
#include "../components/transform.hpp"
#include "../ecs/ECSManager.hpp"

void Physics2DSystem::update(float dt) {
  for (auto const& entity : entities) {
    auto& transform = ecsManager->getComponent<Transform2D>(entity);
    transform.position += transform.velocity * dt;
  }
}

void Physics2DSystem::init(const std::shared_ptr<EcsManager>& _ecsManager) {
  ecsManager = _ecsManager;
  Signature signature;
  signature.set(ecsManager->getComponentType<Transform2D>());
  ecsManager->setSystemSignature<Physics2DSystem>(signature);
}
