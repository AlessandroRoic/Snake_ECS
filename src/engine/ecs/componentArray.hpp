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
class ComponentArray final : public ComponentArrayInterface {
  std::array<T, MAX_ENTITIES> components;
  std::unordered_map<EntityId, size_t> entityToIndexMap;
  std::unordered_map<size_t, EntityId> indexToEntityMap;
  size_t size{};

 public:
  void insertData(const EntityId entity, T component) {
    assert(!entityToIndexMap.contains(entity) &&
           "Component added to same entity more than once.");

    size_t newIndex = size;
    entityToIndexMap[entity] = newIndex;
    indexToEntityMap[newIndex] = entity;
    components[newIndex] = component;
    ++size;
  }

  void removeData(const EntityId entity) {
    assert(entityToIndexMap.contains(entity) &&
           "Removing non-existent component.");

    size_t indexOfRemovedEntity = entityToIndexMap[entity];
    size_t indexOfLastElement = size - 1;
    components[indexOfRemovedEntity] = components[indexOfLastElement];

    const EntityId entityOfLastElement = indexToEntityMap[indexOfLastElement];
    entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    entityToIndexMap.erase(entity);
    indexToEntityMap.erase(indexOfLastElement);

    --size;
  }

  T& getData(const EntityId entity) {
    if (!entityToIndexMap.contains(entity)) {
      printf("%d /n", entity);
    }
    if (!entityToIndexMap.contains(entity)) {
      printf("ENTITY NOT FOUND");
    }
    assert(entityToIndexMap.contains(entity) &&
           "Retrieving non-existent component.");

    return components[entityToIndexMap[entity]];
  }

  void entityDestroyed(const EntityId entity) override {
    if (entityToIndexMap.contains(entity)) {
      removeData(entity);
    }
  }
};

#endif  //SNAKE_ECS_COMPONENTARRAY_HPP
