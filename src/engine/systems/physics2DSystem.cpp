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
