#include "eventManager.hpp"
#include <format>

void EventManager::subscribe(EventType eventType,
                             const CallbackFunctionPtr& callback) {
  if (eventCallbacks.empty()) {
    eventCallbacks.emplace(eventType,
                           std::vector<CallbackFunctionPtr>{callback});
  } else {
    eventCallbacks[eventType].emplace_back(callback);
  }
}

void EventManager::fire(const Event* event) {
  const auto& eventType = event->type;
  auto iterator = eventCallbacks.find(eventType);
  if (iterator != eventCallbacks.end()) {
    const auto& callbacks = iterator->second;

    if (callbacks.empty())
      return;

    for (const auto& callback : callbacks) {
      if (callback) {
        (*callback)(event);
      }
    }
  }
}

void EventManager::unsubscribe(EventType eventType,
                               const CallbackFunctionPtr& callback) {
  auto iterator = eventCallbacks.find(eventType);
  if (iterator == eventCallbacks.end())
    return;

  auto& callbacks = iterator->second;

  if (callbacks.empty())
    return;

  auto iter = std::find(callbacks.begin(), callbacks.end(), callback);
  if (iter != callbacks.end()) {
    callbacks.erase(iter);
  }
}
