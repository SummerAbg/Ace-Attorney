#pragma once

#include "at_Basic.h"
#include "at_TypeConvert.h"

namespace AsciiTools {
template <typename T> class Serialization {
public:
  Serialization() = default;
  Serialization(const T &obj) : obj(obj) {}

  std::string getSerializationStr() const;

private:
  T obj;
};

template <typename T> std::string serializeType(const T &arg) {
  Serialization<T> srl(arg);
  return "[" + srl.getSerializationStr() + "]";
}

template <typename T, typename... Args>
std::string serializeType(const T &arg, const Args &...args) {
  return serializeType(arg) + serializeType(args...);
}

template <typename T>
inline std::string Serialization<T>::getSerializationStr() const {
  if constexpr (!std::is_base_of_v<AsciiBasicObject, T>) {
    if constexpr (std::is_same_v<T, char>) {
      return std::to_string(static_cast<int>(obj));
    }
    TypeDecorator<std::string, T> decorator(obj);
    return decorator.toTargetType();
  } else {
    return serialize(&obj);
  }
}
} // namespace AsciiTools