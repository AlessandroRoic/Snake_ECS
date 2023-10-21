#ifndef SNAKE_ECS_COMPONENTARRAY_HPP
#define SNAKE_ECS_COMPONENTARRAY_HPP

#include <cassert>
#include <unordered_map>
#include "types.hpp"

class ComponentArrayInterface {
 public:
  virtual ~ComponentArrayInterface() = default;
  virtual void entityDestroyed(EntityId entity) = 0;
};

template <typename T>
class ComponentArray : public ComponentArrayInterface {
  std::array<T, MAX_ENTITIES> components;
  std::unordered_map<EntityId, size_t> entityToIndexMap;
  std::unordered_map<size_t, EntityId> indexToEntityMap;
  size_t size{};

 public:
  void insertData(EntityId entity, T component) {
    assert(entityToIndexMap.find(entity) == entityToIndexMap.end() &&
           "Component added to same entity more than once.");

    size_t newIndex = size;
    entityToIndexMap[entity] = newIndex;
    indexToEntityMap[newIndex] = entity;
    components[newIndex] = component;
    ++size;
  }

  void removeData(EntityId entity) {
    assert(entityToIndexMap.find(entity) != entityToIndexMap.end() &&
           "Removing non-existent component.");

    size_t indexOfRemovedEntity = entityToIndexMap[entity];
    size_t indexOfLastElement = size - 1;
    components[indexOfRemovedEntity] = components[indexOfLastElement];

    EntityId entityOfLastElement = indexToEntityMap[indexOfLastElement];
    entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    entityToIndexMap.erase(entity);
    indexToEntityMap.erase(indexOfLastElement);

    --size;
  }

  T& getData(EntityId entity) {
    assert(entityToIndexMap.find(entity) != entityToIndexMap.end() &&
           "Retrieving non-existent component.");

    return components[entityToIndexMap[entity]];
  }

  void entityDestroyed(EntityId entity) override {
    if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
      removeData(entity);
    }
  }
};

#endif  //SNAKE_ECS_COMPONENTARRAY_HPP
