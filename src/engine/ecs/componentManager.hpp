#ifndef SNAKE_ECS_COMPONENTMANAGER_HPP
#define SNAKE_ECS_COMPONENTMANAGER_HPP

#include <memory>
#include <unordered_map>
#include "componentArray.hpp"
#include "types.hpp"

class ComponentManager {

  // Map from type string pointer to a component type
  std::unordered_map<const char*, ComponentTypeId> componentTypes{};

  // Map from type string pointer to a component array
  // TODO: rename
  std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>>
      componentArrays{};

  // The component type to be assigned to the next registered component - starting at 0
  ComponentTypeId nextComponentType{};

  // Convenience function to get the statically casted pointer to the ComponentArray of type T.
  template <typename T>
  std::shared_ptr<ComponentArray<T>> getComponentArray() {
    const char* typeName = typeid(T).name();

    assert(componentTypes.find(typeName) != componentTypes.end() &&
           "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(
        componentArrays[typeName]);
  }

 public:
  template <typename T>
  void registerComponent() {
    const char* typeName = typeid(T).name();

    assert(componentTypes.find(typeName) == componentTypes.end() &&
           "Registering component type more than once.");

    // Add this component type to the component type map
    componentTypes.insert({typeName, nextComponentType});

    // Create a ComponentArray pointer and add it to the component arrays map
    componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    ++nextComponentType;
  }

  template <typename T>
  ComponentTypeId getComponentType() {
    const char* typeName = typeid(T).name();

    assert(componentTypes.find(typeName) != componentTypes.end() &&
           "Component not registered before use.");

    // Return this component's type - used for creating signatures
    return componentTypes[typeName];
  }

  template <typename T>
  void addComponent(EntityId entity, T component) {
    // Add a component to the array for an entity
    getComponentArray<T>()->insertData(entity, component);
  }

  template <typename T>
  void removeComponent(EntityId entity) {
    // Remove a component from the array for an entity
    getComponentArray<T>()->removeData(entity);
  }

  template <typename T>
  T& getComponent(EntityId entity) {
    // Get a reference to a component from the array for an entity
    return getComponentArray<T>()->getData(entity);
  }

  void entityDestroyed(EntityId entity) {
    // Notify each component array that an entity has been destroyed
    // If it has a component for that entity, it will remove it
    for (auto const& pair : componentArrays) {
      auto const& component = pair.second;

      component->entityDestroyed(entity);
    }
  }
};

#endif  //SNAKE_ECS_COMPONENTMANAGER_HPP
