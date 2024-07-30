#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace AsciiTools {
#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__ __PRETTY_FUNCTION__
#endif

template <typename Type> struct Coordinate2d;
struct AsciiColor;
struct AsciiTextColor;

typedef Coordinate2d<int> Vec2d;
typedef Coordinate2d<int> Coord2d;

template <typename Type> using Coord = Coordinate2d<Type>;
using Point2D = Coord2d;                                // 二维点坐标
using AsciiTrprData = std::vector<bool>;                // 透明数据
using AsciiColorData = std::vector<AsciiColor>;         // 颜色数据
using AsciiTextColorData = std::vector<AsciiTextColor>; // 文本颜色数据

// 分割字符串
std::vector<std::string> split(const std::string &str, char chr);

class AsciiBasicObject;

// 设置字体颜色
void setWordColor(AsciiColor color);
// 设置背景颜色
void setBackgroundColor(AsciiColor color);

// 混合两个颜色(color1占主导地位)
AsciiColor mixAsciiColor(AsciiColor color1, AsciiColor color2);
AsciiTextColor mixAsciiTextColor(AsciiTextColor color1, AsciiTextColor color2);

// 获取字符串行数
int getStringLineCount(const std::string &str);
// 按行截取字符串(line1-line2)
std::string interceptString(const std::string &str, int line1, int line2);
// 拼接字符串
std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs);

// 括号匹配
std::vector<std::string> bracketMatch(const std::string &str,
                                      int layerCount = 1,
                                      char leftBracket = '[',
                                      char rightBracket = ']');

// 按比例根据长宽获取新坐标
Coord2d getCoord(int length, int width, double px, double py);

// 平均分配容器中的元素至若干个新容器中
template <typename T>
std::vector<std::vector<T>> equalDivision(int count,
                                          const std::vector<T> &vec) {
  std::vector<std::vector<T>> ret;

  const int numElement = vec.size() / count;
  bool isPerfectDivision = (vec.size() % count == 0);

  for (int i = 0; i < count; i++) {
    std::vector<T> temp;
    int size = 0;
    if (i < count - 1 || isPerfectDivision) {
      size = numElement;
    } else {
      size = vec.size() - numElement * (count - 1);
    }

    for (int j = 0; j < size; j++) {
      temp.emplace_back(vec[i * numElement + j]);
    }
    ret.emplace_back(temp);
  }
  return ret;
}
} // namespace AsciiTools