#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "collisionSystem.hpp"
#include "ecs/ECSManager.hpp"
#include "ecs/system.hpp"

class CollisionSystem : public System {
  std::shared_ptr<EcsManager> ecsManager;
  std::unordered_map<EntityId, EntityId> collidedEntities{};

 public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager);
  void update(const EntityId& snakeEntityId);
};

#endif  //COLLISIONSYSTEM_HPP
