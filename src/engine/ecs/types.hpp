#ifndef SNAKE_ECS_TYPES_HPP
#define SNAKE_ECS_TYPES_HPP

#include <bitset>
#include <cstdint>

using EntityId = std::uint32_t;

constexpr EntityId MAX_ENTITIES = 5000;

using ComponentTypeId = std::uint8_t;

constexpr ComponentTypeId MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

#endif  //SNAKE_ECS_TYPES_HPP
