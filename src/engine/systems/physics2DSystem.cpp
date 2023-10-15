#include "physics2DSystem.hpp"
#include "../components/transform.hpp"
#include "../ecs/ecsPlaceholder.hpp"

void Physics2DSystem::update(float dt) {
  for (auto const& entity : entities) {
    auto& transform =
        EcsPlaceholder::getInstance().getComponent<Transform2D>(entity);
    transform.position += transform.velocity * dt;
  }
}

std::shared_ptr<Physics2DSystem> Physics2DSystem::init() {
  auto& ecsPlaceholder = EcsPlaceholder::getInstance();
  auto physics2DSystem = ecsPlaceholder.registerSystem<Physics2DSystem>();
  Signature signature;
  signature.set(ecsPlaceholder.getComponentType<Transform2D>());
  ecsPlaceholder.setSystemSignature<Physics2DSystem>(signature);
  return physics2DSystem;
}
