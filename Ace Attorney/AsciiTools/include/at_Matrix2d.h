#pragma once

#include "at_BasicObject.h"
#include "at_Coordinate2d.h"
#include "at_Deserialization.h"
#include "at_Exception.h"
#include "at_Serialization.h"
#include "at_TypeConvert.h"
#include <vector>

namespace AsciiTools {
const int paramCount_matrix2d = 3;

template <typename Element> class Matrix2d : public AsciiBasicObject {
public:
  using pElements = std::shared_ptr<std::vector<Element>>;
  using Elements = std::vector<Element>;

  Matrix2d();
  Matrix2d(int length, int width, const Element &element);
  Matrix2d(const Matrix2d<Element> &matrix);

  auto begin() const { return elements->begin(); }
  auto end() const { return elements->end(); }

  int getLength() const { return length; }
  int getWidth() const { return width; }

  // 只适用于使用了Matrix2d的情况下
  void setLength(int length);
  void setWidth(int width);

  size_t size() const { return elements->size(); }

  Element &operator[](const Coord2d &coord);
  Element &operator()(int x, int y);
  const Element &operator[](const Coord2d &coord) const;
  const Element &operator()(int x, int y) const;

  Elements getElements() const { return *elements; }

  void append(const Element &element) { elements->emplace_back(element); }

  virtual void operator=(const Matrix2d<Element> &matrix);

  virtual bool operator==(const Matrix2d<Element> &matrix) const;
  virtual bool operator!=(const Matrix2d<Element> &matrix) const;

  bool checkCoordinate(const Coord2d &coord) const;

  void show() const;

  void info() const;
  std::string toString() const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

protected:
  int length;
  int width;
  pElements elements;
};

template <typename Element> inline Matrix2d<Element>::Matrix2d() {
  this->length = 0;
  this->width = 0;
  elements = std::make_shared<Elements>(length * width, Element());
}

template <typename Element>
inline Matrix2d<Element>::Matrix2d(int length, int width,
                                   const Element &element) {
  this->length = length;
  this->width = width;
  elements = std::make_shared<Elements>(length * width, element);
}

template <typename Element>
inline Matrix2d<Element>::Matrix2d(const Matrix2d<Element> &matrix) {
  this->length = matrix.getLength();
  this->width = matrix.getWidth();
  this->elements = std::make_shared<Elements>(matrix.getElements());
}

template <typename Element>
inline void Matrix2d<Element>::setLength(int length) {
  this->length = length;
}

template <typename Element> inline void Matrix2d<Element>::setWidth(int width) {
  this->width = width;
}

template <typename Element>
inline Element &Matrix2d<Element>::operator[](const Coord2d &coord) {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*elements)[coord.x + coord.y * length];
}

template <typename Element>
inline Element &Matrix2d<Element>::operator()(int x, int y) {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*elements)[x + y * length];
}

template <typename Element>
inline const Element &
Matrix2d<Element>::operator[](const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*elements)[coord.x + coord.y * length];
}

template <typename Element>
inline const Element &Matrix2d<Element>::operator()(int x, int y) const {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*elements)[x + y * length];
}

template <typename Element>
inline void Matrix2d<Element>::operator=(const Matrix2d<Element> &matrix) {
  this->length = matrix.getLength();
  this->width = matrix.getWidth();
  this->elements = std::make_shared<Elements>(matrix.getElements());
}

template <typename Element>
inline bool
Matrix2d<Element>::operator==(const Matrix2d<Element> &matrix) const {
  return (this->length == matrix.getLength() &&
          this->width == matrix.getWidth() &&
          *this->elements == Elements(matrix.begin(), matrix.end()))
             ? true
             : false;
}

template <typename Element>
inline bool
Matrix2d<Element>::operator!=(const Matrix2d<Element> &matrix) const {
  return !(*this == matrix);
}

template <typename Element>
inline bool Matrix2d<Element>::checkCoordinate(const Coord2d &coord) const {
  return (coord.x >= 0 && coord.x < length && coord.y >= 0 && coord.y < width)
             ? true
             : false;
}

template <typename Element> inline void Matrix2d<Element>::show() const {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      std::cout << (*this)(j, i);
    }
    std::cout << std::endl;
  }
}

template <typename Element> inline void Matrix2d<Element>::info() const {
  std::cout << "Matrix2d<" << typeid(Element).name() << ">对象" << std::endl;
  show();
}

template <typename Element>
inline std::string Matrix2d<Element>::toString() const {
  std::string ret;
  for (const auto &index : *this) {
    TypeDecorator<std::string, Element> decorator(index);
    ret += decorator.toTargetType();
  }
  return ret;
}

template <typename Element>
inline std::string Matrix2d<Element>::getSerializeStr() const {
  std::string str_elements;
  for (const Element &index : *this) {
    str_elements += serializeType(index);
  }
  return serializeType(length, width, str_elements);
}

template <typename Element>
inline void Matrix2d<Element>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() != paramCount_matrix2d) {
    throw AsciiBasicException(
        __FUNC__, "str->matrix2d时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_matrix2d) + ")");
  }

  deserializeType(length, tokens[0]);
  deserializeType(width, tokens[1]);

  elements = std::make_shared<Elements>(length * width, Element());

  const auto params = bracketMatch(tokens[2]);
  for (int i = 0; i < (*elements).size(); i++) {
    deserializeType((*elements)[i], params[i]);
  }
}
} // namespace AsciiTools