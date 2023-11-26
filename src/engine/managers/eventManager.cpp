#include "eventManager.hpp"

#include <ranges>

void EventManager::subscribe(EventType eventType,
                             const CallbackFunctionPtr& callback) {
  if (eventCallbacks.empty()) {
    eventCallbacks.emplace(eventType, std::vector{callback});
  } else {
    eventCallbacks[eventType].emplace_back(callback);
  }
}

void EventManager::fire(const Event* event) {
  const auto& eventType = event->type;
  const auto iterator = eventCallbacks.find(eventType);
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

void EventManager::unsubscribe(const EventType eventType,
                               const CallbackFunctionPtr& callback) {
  const auto iterator = eventCallbacks.find(eventType);
  if (iterator == eventCallbacks.end())
    return;

  auto& callbacks = iterator->second;

  if (callbacks.empty())
    return;

  if (const auto iter = std::ranges::find(callbacks, callback);
      iter != callbacks.end()) {
    callbacks.erase(iter);
  }
}

void EventManager::subscribe(SDL_EventType eventType,
                             const SDLCallbackFunctionPtf& callback) {
  if (sdlEventCallbacks.empty()) {
    sdlEventCallbacks.emplace(eventType, std::vector{callback});
  } else {
    sdlEventCallbacks[eventType].emplace_back(callback);
  }
}

void EventManager::fire(const SDL_Event* event) {
  const auto& eventType = event->type;
  if (const auto iterator =
          sdlEventCallbacks.find(static_cast<const SDL_EventType>(eventType));
      iterator != sdlEventCallbacks.end()) {
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

void EventManager::unsubscribe(const SDL_EventType eventType,
                               const SDLCallbackFunctionPtf& callback) {
  const auto iterator = sdlEventCallbacks.find(eventType);
  if (iterator == sdlEventCallbacks.end())
    return;

  auto& callbacks = iterator->second;

  if (callbacks.empty())
    return;

  if (const auto iter = std::ranges::find(callbacks, callback);
      iter != callbacks.end()) {
    callbacks.erase(iter);
  }
}

void EventManager::unsubscribeAll() {
  for (auto& callback : std::views::values(eventCallbacks)) {
    callback.clear();
  }
  eventCallbacks.clear();

  for (auto& callback : std::views::values(sdlEventCallbacks)) {
    callback.clear();
  }
  sdlEventCallbacks.clear();
}
