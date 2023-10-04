#ifndef SNAKE_ECS_OBSERVER_HPP
#define SNAKE_ECS_OBSERVER_HPP

#include <any>
#include <string>

class Observer {
 public:
  virtual void update(const std::string& event, const std::any& eventData) = 0;
};

#endif  //SNAKE_ECS_OBSERVER_HPP
