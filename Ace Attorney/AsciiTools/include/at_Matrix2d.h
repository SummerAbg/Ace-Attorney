#pragma once

#include "at_BasicObject.h"
#include "at_Coordinate2d.h"
#include "at_Deserialization.h"
#include "at_Exception.h"
#include "at_Serialization.h"
#include "at_TypeConvert.h"
#include <vector>

namespace AsciiTools {
const int paramCount_matrix2d_element = 2;
const int paramCount_matrix2d = 4;

template <typename ElementType>
struct Matrix2dElement : public AsciiBasicObject {
public:
  Coord2d coord;
  ElementType element;

  Matrix2dElement() = default;
  Matrix2dElement(const Coord2d &coord, const ElementType &element);

  bool operator==(const Matrix2dElement<ElementType> &element) const;
  bool operator==(Matrix2dElement<ElementType> &&element) const noexcept;

  bool operator!=(const Matrix2dElement<ElementType> &element) const;
  bool operator!=(Matrix2dElement<ElementType> &&element) const noexcept;

  void info() const;
  std::string toString() const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);
};

template <typename ElementType> class Matrix2d : public AsciiBasicObject {
public:
  using Element = Matrix2dElement<ElementType>; // 带有坐标的元素
  using Elements = std::vector<Element>;        // 存储元素的容器
  using pElements = std::shared_ptr<Elements>;  // 容器指针

  Matrix2d();
  Matrix2d(int length, int width, const ElementType &element);
  Matrix2d(const Matrix2d<ElementType> &matrix);
  Matrix2d(Matrix2d<ElementType> &&matrix) noexcept;

  auto begin() const { return elements->begin(); }
  auto end() const { return elements->end(); }

  int getLength() const { return length; }
  int getWidth() const { return width; }

  // 只适用于使用了Matrix2d()的情况下
  void setLength(int length);
  void setWidth(int width);

  size_t size() const { return elements->size(); }

  ElementType &operator[](const Coord2d &coord);
  ElementType &operator()(int x, int y);

  ElementType getElement(const Coord2d &coord) const;
  ElementType getElement(int x, int y) const;

  const ElementType &operator[](const Coord2d &coord) const;
  const ElementType &operator()(int x, int y) const;

  Elements getElements() const { return *elements; }
  ElementType getBackgroundElement() const { return background_element; }

  void append(const Element &element) { elements->emplace_back(element); }

  Matrix2d<ElementType> &operator=(const Matrix2d<ElementType> &matrix);

  bool operator==(const Matrix2d<ElementType> &matrix) const;
  bool operator==(Matrix2d<ElementType> &&matrix) const noexcept;

  bool operator!=(const Matrix2d<ElementType> &matrix) const;
  bool operator!=(Matrix2d<ElementType> &&matrix) const noexcept;

  bool checkCoordinate(const Coord2d &coord) const;
  bool checkCoordinate(Coord2d &&coord) const noexcept;

  bool isElementCoord(const Coord2d &coord) const;

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
  ElementType background_element;
};

template <typename Element> inline Matrix2d<Element>::Matrix2d() {
  this->length = 0;
  this->width = 0;
  elements = std::make_shared<Elements>();
}

template <typename ElementType>
inline Matrix2d<ElementType>::Matrix2d(int length, int width,
                                       const ElementType &element) {
  this->length = length;
  this->width = width;
  elements = std::make_shared<Elements>();
  background_element = element;
}

template <typename ElementType>
inline Matrix2d<ElementType>::Matrix2d(const Matrix2d<ElementType> &matrix) {
  this->length = matrix.length;
  this->width = matrix.width;
  this->elements = std::make_shared<Elements>(*matrix.elements);
  this->background_element = matrix.background_element;
}

template <typename ElementType>
inline Matrix2d<ElementType>::Matrix2d(
    Matrix2d<ElementType> &&matrix) noexcept {
  this->length = matrix.length;
  this->width = matrix.width;
  this->elements = matrix.elements;
  this->background_element = matrix.background_element;

  matrix.elements = nullptr;
}

template <typename ElementType>
inline void Matrix2d<ElementType>::setLength(int length) {
  this->length = length;
}

template <typename ElementType>
inline void Matrix2d<ElementType>::setWidth(int width) {
  this->width = width;
}

template <typename ElementType>
inline ElementType &Matrix2d<ElementType>::operator[](const Coord2d &coord) {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  for (auto &index : *elements) {
    if (coord == index.coord) {
      return index.element;
    }
  }
  elements->emplace_back(
      Matrix2dElement<ElementType>(coord, background_element));
  return (*elements)[elements->size() - 1].element;
}

template <typename ElementType>
inline ElementType &Matrix2d<ElementType>::operator()(int x, int y) {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*this)[Vec2d(x, y)];
}

template <typename ElementType>
inline ElementType
Matrix2d<ElementType>::getElement(const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  for (auto &index : *elements) {
    if (coord == index.coord) {
      return index.element;
    }
  }
  elements->emplace_back(
      Matrix2dElement<ElementType>({coord, background_element}));
  return (*elements)[elements->size() - 1].element;
}

template <typename ElementType>
inline ElementType Matrix2d<ElementType>::getElement(int x, int y) const {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return getElement(Vec2d(x, y));
}

template <typename ElementType>
inline const ElementType &
Matrix2d<ElementType>::operator[](const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return this->getElement(coord);
}

template <typename ElementType>
inline const ElementType &Matrix2d<ElementType>::operator()(int x,
                                                            int y) const {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return this->getElement(x, y);
}

template <typename ElementType>
inline Matrix2d<ElementType> &
Matrix2d<ElementType>::operator=(const Matrix2d<ElementType> &matrix) {
  this->length = matrix.length;
  this->width = matrix.width;
  this->background_element = matrix.background_element;
  *this->elements = *matrix.elements;

  return *this;
}

template <typename ElementType>
inline bool
Matrix2d<ElementType>::operator==(const Matrix2d<ElementType> &matrix) const {
  return (this->length == matrix.length && this->width == matrix.width &&
          this->background_element == matrix.background_element &&
          *this->elements == Elements(matrix.begin(), matrix.end()))
             ? true
             : false;
}

template <typename ElementType>
inline bool Matrix2d<ElementType>::operator==(
    Matrix2d<ElementType> &&matrix) const noexcept {
  bool ret = (this->length == matrix.length && this->width == matrix.width &&
              this->background_element == matrix.background_element &&
              *this->elements == Elements(matrix.begin(), matrix.end()))
                 ? true
                 : false;
  matrix.elements = nullptr;

  return ret;
}

template <typename ElementType>
inline bool
Matrix2d<ElementType>::operator!=(const Matrix2d<ElementType> &matrix) const {
  return !(*this == matrix);
}

template <typename ElementType>
inline bool Matrix2d<ElementType>::operator!=(
    Matrix2d<ElementType> &&matrix) const noexcept {
  return !(*this == std::move(matrix));
}

template <typename ElementType>
inline bool Matrix2d<ElementType>::checkCoordinate(const Coord2d &coord) const {
  return (coord.x >= 0 && coord.x < length && coord.y >= 0 && coord.y < width)
             ? true
             : false;
}

template <typename ElementType>
inline bool
Matrix2d<ElementType>::checkCoordinate(Coord2d &&coord) const noexcept {
  return (coord.x >= 0 && coord.x < length && coord.y >= 0 && coord.y < width)
             ? true
             : false;
}

template <typename ElementType>
inline bool Matrix2d<ElementType>::isElementCoord(const Coord2d &coord) const {
  for (const auto &index : *elements) {
    if (index.coord == coord) {
      return true;
    }
  }
  return false;
}

template <typename ElementType>
inline void Matrix2d<ElementType>::show() const {
  std::cout << this->toString() << std::endl;
}

template <typename ElementType>
inline void Matrix2d<ElementType>::info() const {
  std::cout << "Matrix2d<" << typeid(ElementType).name() << ">对象"
            << std::endl;
  std::cout << "length:" << length << std::endl;
  std::cout << "width:" << width << std::endl;
  std::cout << "background_element:" << background_element << std::endl;
  show();
}

template <typename ElementType>
inline std::string Matrix2d<ElementType>::toString() const {
  std::string ret;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      TypeDecorator<std::string, ElementType> decorator;

      bool isElement = isElementCoord(Vec2d(j, i));
      if (isElement) {
        decorator.init(this->getElement(j, i));
      } else {
        decorator.init(background_element);
      }
      ret += decorator.toTargetType();
      ret += "\t";
    }
    ret += "\n";
  }
  return ret;
}

template <typename ElementType>
inline std::string Matrix2d<ElementType>::getSerializeStr() const {
  std::string str_elements;

  for (const Element &index : *elements) {
    str_elements += serializeType(index);
  }
  return serializeType(length, width, str_elements, background_element);
}

template <typename ElementType>
inline void Matrix2d<ElementType>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() != paramCount_matrix2d) {
    throw AsciiBasicException(
        __FUNC__, "str->matrix2d时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_matrix2d) + ")");
  }

  deserializeType(length, tokens[0]);
  deserializeType(width, tokens[1]);

  const auto tokens_elements = bracketMatch(tokens[2]);
  const int size_elements = static_cast<int>(tokens_elements.size());

  elements = std::make_shared<Elements>(size_elements);

  for (int i = 0; i < size_elements; i++) {
    const auto tokens_matrix2d_element = bracketMatch(tokens_elements[i]);

    const auto str_coord = tokens_matrix2d_element[0];
    const auto str_element = tokens_matrix2d_element[1];

    deserializeType((*elements)[i].coord, str_coord);
    deserializeType((*elements)[i].element, str_element);
  }

  deserializeType(background_element, tokens[3]);
}

template <typename ElementType>
inline Matrix2dElement<ElementType>::Matrix2dElement(
    const Coord2d &coord, const ElementType &element) {
  this->coord = coord;
  this->element = element;
}

template <typename ElementType>
inline bool Matrix2dElement<ElementType>::operator==(
    const Matrix2dElement<ElementType> &element) const {
  return (this->coord == element.coord && this->element == element.element)
             ? true
             : false;
}

template <typename ElementType>
inline bool Matrix2dElement<ElementType>::operator==(
    Matrix2dElement<ElementType> &&element) const noexcept {
  return (this->coord == element.coord && this->element == element.element)
             ? true
             : false;
}

template <typename ElementType>
inline bool Matrix2dElement<ElementType>::operator!=(
    const Matrix2dElement<ElementType> &element) const {
  return !(*this == element);
}

template <typename ElementType>
inline bool Matrix2dElement<ElementType>::operator!=(
    Matrix2dElement<ElementType> &&element) const noexcept {
  return !(*this == std::move(element));
}

template <typename ElementType>
inline void Matrix2dElement<ElementType>::info() const {
  std::cout << "Matrix2dElement<" << typeid(ElementType).name() << ">对象"
            << std::endl;
  std::cout << "coord:" << coord.toString() << std::endl;
  std::cout << "element:" << element << std::endl;
}

template <typename ElementType>
inline std::string Matrix2dElement<ElementType>::toString() const {
  return spliceString(",", coord, element);
}

template <typename ElementType>
inline std::string Matrix2dElement<ElementType>::getSerializeStr() const {
  return serializeType(coord, element);
}

template <typename ElementType>
inline void
Matrix2dElement<ElementType>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  if (tokens.size() != 2) {
    throw AsciiBasicException(
        __FUNC__, "str->Matrix2dElement时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_matrix2d_element) + ")");
  }
  deserializeType(coord, tokens[0]);
  deserializeType(element, tokens[1]);
}
} // namespace AsciiTools