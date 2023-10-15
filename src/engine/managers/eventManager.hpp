#ifndef SNAKE_ECS_EVENTMANAGER_HPP
#define SNAKE_ECS_EVENTMANAGER_HPP

#include <any>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

enum EventType { KEY_PRESSED };

struct Event {
  EventType type{};
  explicit Event(EventType _type) : type(_type) {}
  virtual ~Event() = default;
};

using CallbackFunction = std::function<void(const Event*)>;
using CallbackFunctionPtr = std::shared_ptr<CallbackFunction>;
class EventManager {
  std::unordered_map<EventType, std::vector<CallbackFunctionPtr>>
      eventCallbacks{};

 public:
  void subscribe(EventType eventType, const CallbackFunctionPtr& callback);

  void fire(const Event* event);

  void unsubscribe(EventType eventType, const CallbackFunctionPtr& callback);
};

#endif  //SNAKE_ECS_EVENTMANAGER_HPP
