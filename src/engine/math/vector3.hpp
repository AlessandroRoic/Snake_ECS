#ifndef SNAKE_ECS_VECTOR3_HPP
#define SNAKE_ECS_VECTOR3_HPP

class Vector3 {
 public:
  float x, y, z;
  Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

  Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

  Vector3 operator+(Vector3 const& rhs) const {
    return {x + rhs.x, y + rhs.y, z + rhs.z};
  }

  Vector3 operator+=(Vector3 const& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
  }

  Vector3 operator-(Vector3 const& rhs) const {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
  }

  Vector3 operator-=(Vector3 const& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
  }

  Vector3 operator*(Vector3 const& rhs) const {
    return {x * rhs.x, y * rhs.y, z * rhs.z};
  }

  Vector3 operator*=(Vector3 const& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;

    return *this;
  }

  Vector3 operator*(const float rhs) const { return {x * rhs, y * rhs, z * rhs}; }

  Vector3 operator*=(const float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;

    return *this;
  }
};

#endif  //SNAKE_ECS_VECTOR3_HPP
