#pragma once

#include "at_Basic.h"
#include "at_Exception.h"
#include "at_Serialization.h"
#include "at_TypeConvert.h"
#include <type_traits>

namespace AsciiTools {
// 2D坐标
template <typename Type> struct Coordinate2d : public AsciiBasicObject {
public:
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

  Coordinate2d<Type> operator+(const Coordinate2d &coord) const;
  Coordinate2d<Type> operator-(const Coordinate2d &coord) const;
  Coordinate2d<Type> operator*(const Coordinate2d &coord) const;
  Coordinate2d<Type> operator/(const Coordinate2d &coord) const;

  Coordinate2d<Type> operator+=(const Coordinate2d &coord);
  Coordinate2d<Type> operator-=(const Coordinate2d &coord);
  Coordinate2d<Type> operator*=(const Coordinate2d &coord);
  Coordinate2d<Type> operator/=(const Coordinate2d &coord);

  Coordinate2d<Type> operator()(Type deltaX, Type deltaY) const;

  Coordinate2d<Type> &operator=(const Coordinate2d &coord);

  void info() const;
  std::string toString() const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);
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
template <typename Type>
inline Coordinate2d<Type> &
Coordinate2d<Type>::operator=(const Coordinate2d &coord) {
  this->x = coord.x;
  this->y = coord.y;
  return *this;
}

template <typename Type> inline void Coordinate2d<Type>::info() const {
  std::cout << "Coordinate2d<" << typeid(Type).name() << ">对象" << std::endl;
  std::cout << this->toString() << std::endl;
}

template <typename Type>
inline std::string Coordinate2d<Type>::toString() const {
  std::string ret = spliceString(",", x, y);
  return ret;
}

template <typename Type>
inline std::string Coordinate2d<Type>::getSerializeStr() const {
  return serializeType(x, y);
}

template <typename Type>
inline void Coordinate2d<Type>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() < 2) {
    throw AsciiBasicException(__FUNC__, "参数过少!至少为两个!(x,y)");
  }

  auto str_x = tokens[0];
  auto str_y = tokens[1];

  if constexpr (std::is_same_v<Type, int>) {
    *this = Coordinate2d<int>(stringToInt(str_x), stringToInt(str_y));
  } else if constexpr (std::is_same_v<Type, short>) {
    *this = Coordinate2d<short>(stringToShort(str_x), stringToShort(str_y));
  } else if constexpr (std::is_same_v<Type, double>) {
    *this = Coordinate2d<double>(stringToDouble(str_x), stringToDouble(str_y));
  } else {
    throw AsciiBasicException(__FUNC__, "类型异常！(不是int，short或double)");
  }
}
} // namespace AsciiTools