#pragma once

#include "at_BasicString.h"
#include "at_Debug.h"
#include "at_Matrix2d.h"

namespace AsciiTools {
class AsciiBasicObject;

// ����������ɫ
void setWordColor(AsciiColor color);
// ���ñ�����ɫ
void setBackgroundColor(AsciiColor color);
// ���������ɫ(color1ռ������λ)
AsciiColor mixAsciiColor(AsciiColor color1, AsciiColor color2);
AsciiTextColor mixAsciiTextColor(AsciiTextColor color1, AsciiTextColor color2);

// �ָ��ַ���
std::vector<std::string> split(const std::string &str, char chr);

// string->int
int stringToInt(const std::string &str);
// char->int
int charToInt(char chr);
// char->bool
bool charToBool(char chr);
// string->bool
bool stringToBool(const std::string &str);
// int->bool
bool intToBool(int number);
// string->double
double stringToDouble(const std::string &str);

// ��ȡ�ַ�������
int getStringLineCount(const std::string &str);
// ���н�ȡ�ַ���(line1-line2)
std::string interceptString(const std::string &str, int line1, int line2);
// ƴ���ַ���
std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs);

// ����װ����
template <typename Type> class TypeDecorator {
public:
  TypeDecorator(Type obj) : obj(obj) {}

  std::string toString() const;

private:
  Type obj;
};

template <typename T> std::string spliceString(const T &arg) {
  TypeDecorator<T> decorator(arg);
  return decorator.toString();
}

template <typename T>
std::string spliceString(const std::string &str, const T &arg) {
  TypeDecorator<T> decorator(arg);
  return decorator.toString();
}

template <typename T, typename... Args>
std::string spliceString(const std::string &str, const T &arg,
                         const Args &...args) {
  TypeDecorator<T> decorator(arg);
  std::string ret = decorator.toString() + str + spliceString(str, args...);
  return ret;
}

template <typename Type>
inline std::string TypeDecorator<Type>::toString() const {
  if (std::is_same<Type, bool>::value) { // bool
    return obj ? "true" : "false";
  } else if (std::is_integral<Type>::value) { // int
    return std::to_string(obj);
  } else if (std::is_floating_point<Type>::value) { // double or float
    return std::to_string(obj);
  } else {
    throw std::exception("��ȷ��������!�޷�ת����");
  }
}
} // namespace AsciiTools