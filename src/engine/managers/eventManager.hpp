#ifndef SNAKE_ECS_EVENTMANAGER_HPP
#define SNAKE_ECS_EVENTMANAGER_HPP

#include <SDL_events.h>
#include <any>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

enum EventType { INIT, UPDATE, RENDER, RENDER_STOP, CLOSE };

struct Event {
  EventType type{};
  std::any data;
  explicit Event(EventType _type) : type(_type) {}
  virtual ~Event() = default;
};

using CallbackFunction = std::function<void(const Event*)>;
using CallbackFunctionPtr = std::shared_ptr<CallbackFunction>;
using SDLCallbackFunction = std::function<void(const SDL_Event*)>;
using SDLCallbackFunctionPtf = std::shared_ptr<SDLCallbackFunction>;

/**
 * Holds both user and SDL events. It would be more performant and
 * smart to use the SDL2 system directly but that way I don't have
 * control over the events.
 */
class EventManager {
  std::unordered_map<SDL_EventType, std::vector<SDLCallbackFunctionPtf>>
      sdlEventCallbacks{};
  std::unordered_map<EventType, std::vector<CallbackFunctionPtr>>
      eventCallbacks{};

 public:
  void subscribe(EventType eventType, const CallbackFunctionPtr& callback);
  void subscribe(SDL_EventType eventType,
                 const SDLCallbackFunctionPtf& callback);

  void fire(const Event* event);
  void fire(const SDL_Event* event);

  void unsubscribe(EventType eventType, const CallbackFunctionPtr& callback);
  void unsubscribe(SDL_EventType eventType,
                   const SDLCallbackFunctionPtf& callback);
  void unsubscribeAll();
};

#endif  //SNAKE_ECS_EVENTMANAGER_HPP
