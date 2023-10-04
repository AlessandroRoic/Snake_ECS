#ifndef SNAKE_ECS_ENTITYMANAGER_HPP
#define SNAKE_ECS_ENTITYMANAGER_HPP

#include <array>
#include <cassert>
#include <queue>
#include "types.hpp"

class EntityManager {
 private:
  // Queue of unused entity IDs
  std::queue<EntityId> availableEntities{};

  // Array of signatures where the index corresponds to the entity ID
  std::array<Signature, MAX_ENTITIES> signatures{};

  // Total living entities - used to keep limits on how many exist
  uint32_t livingEntityCount{};

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
    EntityId id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;

    return id;
  }

  void destroyEntity(EntityId entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Invalidate the destroyed entity's signature
    signatures[entity].reset();

    // Put the destroyed ID at the back of the queue
    availableEntities.push(entity);
    --livingEntityCount;
  }

  void setSignature(EntityId entity, Signature signature) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Put this entity's signature into the array
    signatures[entity] = signature;
  }

  Signature getSignature(EntityId entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Get this entity's signature from the array
    return signatures[entity];
  }
};

#endif  //SNAKE_ECS_ENTITYMANAGER_HPP
