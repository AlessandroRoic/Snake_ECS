#ifndef SNAKE_ECS_VECTOR2_HPP
#define SNAKE_ECS_VECTOR2_HPP

class Vector2 {
 public:
  float x, y;

  Vector2() : x(0.0f), y(0.0f) {}

  Vector2(float x, float y) : x(x), y(y) {}

  Vector2 operator+(Vector2 const& v) const { return {x + v.x, y + v.y}; }

  Vector2 operator+=(Vector2 const& v) {
    x += v.x;
    y += v.y;

    return *this;
  }

  Vector2 operator-(Vector2 const& v) const { return {x - v.x, y - v.y}; }

  Vector2 operator-=(Vector2 const& v) {
    x -= v.x;
    y -= v.y;

    return *this;
  }

  Vector2 operator*(Vector2 const& rhs) const { return {x * rhs.x, y * rhs.y}; }

  Vector2 operator*=(Vector2 const& rhs) {
    x *= rhs.x;
    y *= rhs.y;

    return *this;
  }

  Vector2 operator*(float rhs) const { return {x * rhs, y * rhs}; }

  Vector2 operator*=(float rhs) {
    x *= rhs;
    y *= rhs;

    return *this;
  }
};

#endif  //SNAKE_ECS_VECTOR2_HPP
