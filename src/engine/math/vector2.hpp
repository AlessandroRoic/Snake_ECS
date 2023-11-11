#ifndef SNAKE_ECS_VECTOR2_HPP
#define SNAKE_ECS_VECTOR2_HPP

class Vector2 {
 public:
  float x, y;

  Vector2() : x(0.0f), y(0.0f) {}

  Vector2(const float x, const float y) : x(x), y(y) {}

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

  Vector2 operator*(const float rhs) const { return {x * rhs, y * rhs}; }

  Vector2 operator*=(const float rhs) {
    x *= rhs;
    y *= rhs;

    return *this;
  }

  float getMagnitude() const { return std::sqrt(x * x + y * y); }

  static Vector2 normalize(Vector2 vec) {
    if (const float length = std::sqrt(vec.x * vec.x + vec.y * vec.y); length != 0) {
      vec.x /= length;
      vec.y /= length;
    }
    return vec;
  }
};

#endif  //SNAKE_ECS_VECTOR2_HPP
