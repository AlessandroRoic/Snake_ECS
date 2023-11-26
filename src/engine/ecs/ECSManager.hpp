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

  EntityId createEntity() const { return entityManager->createEntity(); }

  void destroyEntity(const EntityId entity) const {
    entityManager->destroyEntity(entity);
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
  }

  void destroyEntities(const std::vector<EntityId>& entities) {
    entityManager->destroyEntities(entities);
    componentManager->destroyEntities(entities);
    systemManager->destroyEntities(entities);
  }

  void destroyAllEntities() const {
    for (const EntityId entityId : entityManager->getLivingEntities()) {
      destroyEntity(entityId);
    }
  }

  template <typename T>
  void addComponent(const EntityId entity, T component) {
    componentManager->addComponent<T>(entity, component);

    auto signature = entityManager->getSignature(entity);
    signature.set(componentManager->getComponentType<T>(), true);
    entityManager->setSignature(entity, signature);

    systemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T>
  void removeComponent(const EntityId entity) const {
    componentManager->removeComponent<T>(entity);

    auto signature = entityManager->getSignature(entity);
    signature.set(componentManager->getComponentType<T>(), false);
    entityManager->setSignature(entity, signature);

    systemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T>
  T& getComponent(const EntityId entity) {
    return componentManager->getComponent<T>(entity);
  }

  template <typename T>
  void registerComponent() const {
    componentManager->registerComponent<T>();
  }

  template <typename T>
  ComponentTypeId getComponentType() const {
    return componentManager->getComponentType<T>();
  }

  template <typename T>
  std::shared_ptr<T> registerSystem() {
    return systemManager->registerSystem<T>();
  }

  template <typename T>
  void setSystemSignature(const Signature signature) const {
    systemManager->setSignature<T>(signature);
  }
};

#endif  //SNAKE_ECS_ECSMANAGER_HPP
