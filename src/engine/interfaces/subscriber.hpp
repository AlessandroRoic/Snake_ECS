#ifndef SNAKE_ECS_SUBSCRIBER_HPP
#define SNAKE_ECS_SUBSCRIBER_HPP

#include "observer.hpp"

class Subscriber {
 public:
  virtual void subscribe(Observer* observer) = 0;
  virtual void unsubscribe(Observer* observer) = 0;
  virtual void notify(const std::string& event,
                      const std::any& eventData = std::any()) = 0;
};

#endif  //SNAKE_ECS_SUBSCRIBER_HPP
