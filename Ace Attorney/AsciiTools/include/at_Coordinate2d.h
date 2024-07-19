#pragma once

#include <type_traits>

namespace AsciiTools {
// 2D坐标
template <typename Type> struct Coordinate2d {
  static_assert(std::is_same<Type, int>::value ||
                    std::is_same<Type, double>::value ||
                    std::is_same<Type, short>::value,
                "Type一定是int,double或short");

  Type x;
  Type y;

  Coordinate2d() = default;
  explicit Coordinate2d(Type x, Type y);

  bool operator==(const Coordinate2d &coord) const;
  bool operator!=(const Coordinate2d &coord) const;

  Coordinate2d operator+(const Coordinate2d &coord) const;
  Coordinate2d operator-(const Coordinate2d &coord) const;
  Coordinate2d operator*(const Coordinate2d &coord) const;
  Coordinate2d operator/(const Coordinate2d &coord) const;

  Coordinate2d operator+=(const Coordinate2d &coord);
  Coordinate2d operator-=(const Coordinate2d &coord);
  Coordinate2d operator*=(const Coordinate2d &coord);
  Coordinate2d operator/=(const Coordinate2d &coord);

  Coordinate2d operator()(Type deltaX, Type deltaY) const;
};

template <typename Type> Coordinate2d<Type>::Coordinate2d(Type x, Type y) {
  this->x = x;
  this->y = y;
}

template <typename Type>
bool Coordinate2d<Type>::operator==(const Coordinate2d &coord) const {
  return (this->x == coord.x && this->y == coord.y) ? true : false;
}

template <typename Type>
bool Coordinate2d<Type>::operator!=(const Coordinate2d &coord) const {
  return !(*this == coord);
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator+(const Coordinate2d &coord) const {
  Coordinate2d ret;
  ret.x = this->x + coord.x;
  ret.y = this->y + coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator-(const Coordinate2d &coord) const {
  Coordinate2d ret;
  ret.x = this->x - coord.x;
  ret.y = this->y - coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator*(const Coordinate2d &coord) const {
  Coordinate2d ret;
  ret.x = this->x * coord.x;
  ret.y = this->y * coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator/(const Coordinate2d &coord) const {
  Coordinate2d ret;
  ret.x = this->x / coord.x;
  ret.y = this->y / coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type> Coordinate2d<Type>::operator+=(const Coordinate2d &coord) {
  *this = *this + coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type> Coordinate2d<Type>::operator-=(const Coordinate2d &coord) {
  *this = *this - coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type> Coordinate2d<Type>::operator*=(const Coordinate2d &coord) {
  *this = *this * coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type> Coordinate2d<Type>::operator/=(const Coordinate2d &coord) {
  *this = *this / coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type> Coordinate2d<Type>::operator()(Type deltaX,
                                                  Type deltaY) const {
  Coordinate2d coord = *this;
  coord.x += deltaX;
  coord.y += deltaY;

  return coord;
}
} // namespace AsciiTools