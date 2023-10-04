#ifndef SNAKE_ECS_COMPONENTARRAY_HPP
#define SNAKE_ECS_COMPONENTARRAY_HPP

#include <cassert>
#include <unordered_map>
#include "types.hpp"

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class ComponentArrayInterface {
 public:
  virtual ~ComponentArrayInterface() = default;
  virtual void entityDestroyed(EntityId entity) = 0;
};

// TODO: find better name for class array is also a field, it's a bit misleading
template <typename T>
class ComponentArray : public ComponentArrayInterface {
  std::array<T, MAX_ENTITIES> componentArray;

  // Map from an entity ID to an array index.
  std::unordered_map<EntityId, size_t> entityToIndexMap;

  // Map from an array index to an entity ID.
  std::unordered_map<size_t, EntityId> indexToEntityMap;

  // Total size of valid entries in the array.
  size_t mSize{};

 public:
  void insertData(EntityId entity, T component) {
    assert(entityToIndexMap.find(entity) == entityToIndexMap.end() &&
           "Component added to same entity more than once.");

    // Put new entry at end and update the maps
    size_t newIndex = mSize;
    entityToIndexMap[entity] = newIndex;
    indexToEntityMap[newIndex] = entity;
    componentArray[newIndex] = component;
    ++mSize;
  }

  void removeData(EntityId entity) {
    assert(entityToIndexMap.find(entity) != entityToIndexMap.end() &&
           "Removing non-existent component.");

    // Copy element at end into deleted element's place to maintain density
    size_t indexOfRemovedEntity = entityToIndexMap[entity];
    size_t indexOfLastElement = mSize - 1;
    componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

    // Update map to point to moved spot
    EntityId entityOfLastElement = indexToEntityMap[indexOfLastElement];
    entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    entityToIndexMap.erase(entity);
    indexToEntityMap.erase(indexOfLastElement);

    --mSize;
  }

  T& getData(EntityId entity) {
    assert(entityToIndexMap.find(entity) != entityToIndexMap.end() &&
           "Retrieving non-existent component.");

    // Return a reference to the entity's component
    return componentArray[entityToIndexMap[entity]];
  }

  void entityDestroyed(EntityId entity) override {
    if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
      // Remove the entity's component if it existed
      removeData(entity);
    }
  }
};

#endif  //SNAKE_ECS_COMPONENTARRAY_HPP
