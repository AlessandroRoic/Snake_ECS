#ifndef SNAKE_ECS_ENTITYMANAGER_HPP
#define SNAKE_ECS_ENTITYMANAGER_HPP

#include <array>
#include <cassert>
#include <queue>
#include <set>
#include "types.hpp"

class EntityManager {
  // Queue of unused entity IDs
  std::queue<EntityId> availableEntities{};

  // Array of signatures where the index corresponds to the entity ID
  std::array<Signature, MAX_ENTITIES> signatures{};

  // Total living entities - used to keep limits on how many exist
  uint32_t livingEntityCount{};

  //Keeps track of all living entities
  std::set<EntityId> livingEntities{};

 public:
  EntityManager() {
    // Initialize the queue with all possible entity IDs
    for (EntityId entity = 0; entity < MAX_ENTITIES; ++entity) {
      availableEntities.push(entity);
    }
  }

  EntityId createEntity() {
    assert(livingEntityCount < MAX_ENTITIES &&
           "Too many entities in existence.");

    // Take an ID from the front of the queue
    const EntityId id = availableEntities.front();
    availableEntities.pop();
    livingEntities.insert(id);
    ++livingEntityCount;

    return id;
  }

  void destroyEntity(const EntityId entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Invalidate the destroyed entity's signature
    signatures[entity].reset();

    // Put the destroyed ID at the back of the queue
    availableEntities.push(entity);
    livingEntities.erase(entity);
    --livingEntityCount;
  }

  void destroyEntities(const std::vector<EntityId>& entities) {
    for (auto& entity : entities) {
      destroyEntity(entity);
    }
  }

  std::set<EntityId> getLivingEntities() const { return livingEntities; }

  void setSignature(const EntityId entity, const Signature signature) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Put this entity's signature into the array
    signatures[entity] = signature;
  }

  Signature getSignature(const EntityId entity) const {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Get this entity's signature from the array
    return signatures[entity];
  }
};

#endif  //SNAKE_ECS_ENTITYMANAGER_HPP
