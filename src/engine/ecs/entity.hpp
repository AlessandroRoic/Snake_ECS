#include <utility>
#include "componentManager.hpp"
#include "entityManager.hpp"
#include "systemManager.hpp"
#include "types.hpp"

class Entity {
  EntityId entityId;
  std::shared_ptr<EcsManager> ecsManager;

 public:
  explicit Entity(std::shared_ptr<EcsManager> _ecsManager)
      : ecsManager(std::move(_ecsManager)) {
    entityId = ecsManager->createEntity();
  }

  void destroyEntity() { ecsManager->destroyEntity(entityId); }

  template <typename T>
  void addComponent(T component) {
    ecsManager->addComponent(entityId, component);
  }

  template <typename T>
  T& getComponent() {
    return ecsManager->getComponent<T>(entityId);
  }

  template <typename T>
  void removeComponent() {
    ecsManager->removeComponent<T>(entityId);
  }
};
