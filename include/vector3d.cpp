#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>

namespace nbody {

template<typename T>
struct Vector3
{
  T x{0};
  T y{0};
  T z{0};

  constexpr Vector3& operator+=(const Vector3& vec)
  {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
  }

  constexpr Vector3& operator-=(const Vector3& vec)
  {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
  }

  constexpr Vector3& operator*=(T scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  constexpr Vector3& operator/=(T scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  constexpr T distance2(const Vector3& vec) const
  {
    T dx = x - vec.x;
    T dy = y - vec.y;
    T dz = z - vec.z;
    return dx * dx + dy * dy + dz * dz;
  }

  T distance(const Vector3& vec) const
  {
    return std::sqrt(distance2(vec));
  }

  constexpr T norm2() const
  {
    return x * x + y * y + z * z;
  }

  T norm() const
  {
    return std::sqrt(norm2());
  }
};

template<typename T>
constexpr Vector3<T> operator+(Vector3<T> lhs, const Vector3<T>& rhs)
{
  lhs += rhs;
  return lhs;
}

template<typename T>
constexpr Vector3<T> operator-(Vector3<T> lhs, const Vector3<T>& rhs)
{
  lhs -= rhs;
  return lhs;
}

template<typename T>
constexpr Vector3<T> operator*(Vector3<T> lhs, T scalar)
{
  lhs *= scalar;
  return lhs;
}

template<typename T>
constexpr Vector3<T> operator*(T scalar, Vector3<T> rhs)
{
  rhs *= scalar;
  return rhs;
}

template<typename T>
constexpr Vector3<T> operator/(Vector3<T> lhs, T scalar)
{
  lhs /= scalar;
  return lhs;
}

} // namespace nbody
#endif