#ifndef SNAKE_ECS_ECSPLACEHOLDER_HPP
#define SNAKE_ECS_ECSPLACEHOLDER_HPP
#include "componentManager.hpp"
#include "entityManager.hpp"
#include "systemManager.hpp"

class EcsPlaceholder {
  std::unique_ptr<ComponentManager> componentManager;
  std::unique_ptr<EntityManager> entityManager;
  std::unique_ptr<SystemManager> systemManager;

 public:
  static EcsPlaceholder& getInstance() {
    static EcsPlaceholder instance;
    return instance;
  }

  void init() {
    // Create pointers to each manager
    entityManager = std::make_unique<EntityManager>();
    componentManager = std::make_unique<ComponentManager>();
    systemManager = std::make_unique<SystemManager>();
  }

  EntityId createEntity() { return entityManager->createEntity(); }

  //TODO: make reflective
  void destroyEntity(EntityId entity) {
    entityManager->destroyEntity(entity);
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
  }

  // Component methods
  template <typename T>
  void registerComponent() {
    componentManager->registerComponent<T>();
  }

  //TODO: make reflective
  template <typename T>
  void addComponent(EntityId entity, T component) {
    componentManager->addComponent<T>(entity, component);

    auto signature = entityManager->getSignature(entity);
    signature.set(componentManager->getComponentType<T>(), true);
    entityManager->setSignature(entity, signature);

    systemManager->entitySignatureChanged(entity, signature);
  }

  //TODO: make reflective
  template <typename T>
  void removeComponent(EntityId entity) {
    componentManager->removeComponent<T>(entity);

    auto signature = entityManager->getSignature(entity);
    signature.set(componentManager->getComponentType<T>(), false);
    entityManager->setSignature(entity, signature);

    systemManager->entitySignatureChanged(entity, signature);
  }

  //TODO: make reflective
  template <typename T>
  T& getComponent(EntityId entity) {
    return componentManager->getComponent<T>(entity);
  }

  template <typename T>
  ComponentTypeId getComponentType() {
    return componentManager->getComponentType<T>();
  }

  template <typename T>
  std::shared_ptr<T> registerSystem() {
    return systemManager->registerSystem<T>();
  }

  template <typename T>
  void setSystemSignature(Signature signature) {
    systemManager->setSignature<T>(signature);
  }
};
#endif  //SNAKE_ECS_ECSPLACEHOLDER_HPP
