#ifndef SNAKE_ECS_ECSMANAGER_HPP
#define SNAKE_ECS_ECSMANAGER_HPP
#include "componentManager.hpp"
#include "entityManager.hpp"
#include "systemManager.hpp"

class EcsManager {
 public:
  std::shared_ptr<EntityManager> entityManager =
      std::make_shared<EntityManager>();
  std::shared_ptr<ComponentManager> componentManager =
      std::make_shared<ComponentManager>();
  std::shared_ptr<SystemManager> systemManager =
      std::make_shared<SystemManager>();

  EntityId createEntity() { return entityManager->createEntity(); }

  void destroyEntity(EntityId entity) {
    entityManager->destroyEntity(entity);
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
  }

  template <typename T>
  void registerComponent() {
    componentManager->registerComponent<T>();
  }

  template <typename T>
  void addComponent(EntityId entity, T component) {
    componentManager->addComponent<T>(entity, component);

    auto signature = entityManager->getSignature(entity);
    signature.set(componentManager->getComponentType<T>(), true);
    entityManager->setSignature(entity, signature);

    systemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T>
  void removeComponent(EntityId entity) {
    componentManager->removeComponent<T>(entity);

    auto signature = entityManager->getSignature(entity);
    signature.set(componentManager->getComponentType<T>(), false);
    entityManager->setSignature(entity, signature);

    systemManager->entitySignatureChanged(entity, signature);
  }

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
#endif  //SNAKE_ECS_ECSMANAGER_HPP
