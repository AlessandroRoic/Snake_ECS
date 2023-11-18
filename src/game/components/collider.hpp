#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <functional>

struct Collider {
  std::function<void(EntityId, EntityId)> onCollide;
};

#endif  //COLLIDER_HPP
