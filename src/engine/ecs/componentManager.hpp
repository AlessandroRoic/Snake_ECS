#ifndef SNAKE_ECS_COMPONENTMANAGER_HPP
#define SNAKE_ECS_COMPONENTMANAGER_HPP

#include <memory>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "componentArray.hpp"
#include "types.hpp"

class ComponentManager {

  std::unordered_map<const char*, ComponentTypeId> componentTypes{};

  std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>>
      componentArrays{};

  ComponentTypeId nextComponentType{};

  template <typename T>
  std::shared_ptr<ComponentArray<T>> getComponentArray() {
    const char* typeName = typeid(T).name();

    assert(componentTypes.contains(typeName) &&
           "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(
        componentArrays[typeName]);
  }

 public:
  template <typename T>
  void registerComponent() {
    const char* typeName = typeid(T).name();

    assert(!componentTypes.contains(typeName) &&
           "Registering component type more than once.");

    componentTypes.insert({typeName, nextComponentType});

    componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    ++nextComponentType;
  }

  template <typename T>
  ComponentTypeId getComponentType() {
    const char* typeName = typeid(T).name();

    assert(componentTypes.contains(typeName) &&
           "Component not registered before use.");

    return componentTypes[typeName];
  }

  template <typename T>
  void addComponent(EntityId entity, T component) {
    getComponentArray<T>()->insertData(entity, component);
  }

  template <typename T>
  void removeComponent(EntityId entity) {
    getComponentArray<T>()->removeData(entity);
  }

  template <typename T>
  T& getComponent(EntityId entity) {
    return getComponentArray<T>()->getData(entity);
  }

  void entityDestroyed(const EntityId entity) const {
    for (auto const& component : std::views::values(componentArrays)) {
      component->entityDestroyed(entity);
    }
  }

  void destroyEntities(const std::vector<EntityId>& entities) const {
    for (auto& entity : entities) {
      entityDestroyed(entity);
    }
  }
};

#endif  //SNAKE_ECS_COMPONENTMANAGER_HPP
