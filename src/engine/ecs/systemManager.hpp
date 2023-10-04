#ifndef SNAKE_ECS_SYSTEMMANAGER_HPP
#define SNAKE_ECS_SYSTEMMANAGER_HPP

#include <cassert>
#include <memory>
#include <unordered_map>
#include "system.hpp"
#include "types.hpp"

class SystemManager {

  // Map from system type string pointer to a signature
  std::unordered_map<const char*, Signature> mSignatures{};

  // Map from system type string pointer to a system pointer
  std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};

 public:
  template <typename T>
  std::shared_ptr<T> registerSystem() {
    const char* typeName = typeid(T).name();

    assert(mSystems.find(typeName) == mSystems.end() &&
           "Registering system more than once.");

    // Create a pointer to the system and return it so it can be used externally
    auto system = std::make_shared<T>();
    mSystems.insert({typeName, system});
    return system;
  }

  template <typename T>
  void setSignature(Signature signature) {
    const char* typeName = typeid(T).name();

    assert(mSystems.find(typeName) != mSystems.end() &&
           "System used before registered.");

    // Set the signature for this system
    mSignatures.insert({typeName, signature});
  }

  void entityDestroyed(EntityId entity) {
    // Erase a destroyed entity from all system lists
    // mEntities is a set so no check needed
    for (auto const& pair : mSystems) {
      auto const& system = pair.second;

      system->entities.erase(entity);
    }
  }

  void entitySignatureChanged(EntityId entity, Signature entitySignature) {
    // Notify each system that an entity's signature changed
    for (auto const& pair : mSystems) {
      auto const& type = pair.first;
      auto const& system = pair.second;
      auto const& systemSignature = mSignatures[type];

      // Entity signature matches system signature - insert into set
      if ((entitySignature & systemSignature) == systemSignature) {
        system->entities.insert(entity);
      }
      // Entity signature does not match system signature - erase from set
      else {
        system->entities.erase(entity);
      }
    }
  }
};

#endif  //SNAKE_ECS_SYSTEMMANAGER_HPP
