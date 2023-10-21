#include "eventManager.hpp"

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

void EventManager::subscribe(SDL_EventType eventType,
                             const SDLCallbackFunctionPtf& callback) {
  if (sdlEventCallbacks.empty()) {
    sdlEventCallbacks.emplace(eventType,
                              std::vector<SDLCallbackFunctionPtf>{callback});
  } else {
    sdlEventCallbacks[eventType].emplace_back(callback);
  }
}

void EventManager::fire(const SDL_Event* event) {
  const auto& eventType = event->type;
  auto iterator =
      sdlEventCallbacks.find(static_cast<const SDL_EventType>(eventType));
  if (iterator != sdlEventCallbacks.end()) {
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

void EventManager::unsubscribe(SDL_EventType eventType,
                               const SDLCallbackFunctionPtf& callback) {
  auto iterator = sdlEventCallbacks.find(eventType);
  if (iterator == sdlEventCallbacks.end())
    return;

  auto& callbacks = iterator->second;

  if (callbacks.empty())
    return;

  auto iter = std::find(callbacks.begin(), callbacks.end(), callback);
  if (iter != callbacks.end()) {
    callbacks.erase(iter);
  }
}

void EventManager::unsubscribeAll() {
  for (auto& pair : eventCallbacks) {
    pair.second.clear();
  }
  eventCallbacks.clear();

  for (auto& pair : sdlEventCallbacks) {
    pair.second.clear();
  }
  sdlEventCallbacks.clear();
}
