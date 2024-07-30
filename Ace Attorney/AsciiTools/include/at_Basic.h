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
using Point2D = Coord2d;                                // ��ά������
using AsciiTrprData = std::vector<bool>;                // ͸������
using AsciiColorData = std::vector<AsciiColor>;         // ��ɫ����
using AsciiTextColorData = std::vector<AsciiTextColor>; // �ı���ɫ����

// �ָ��ַ���
std::vector<std::string> split(const std::string &str, char chr);

class AsciiBasicObject;

// ����������ɫ
void setWordColor(AsciiColor color);
// ���ñ�����ɫ
void setBackgroundColor(AsciiColor color);

// ���������ɫ(color1ռ������λ)
AsciiColor mixAsciiColor(AsciiColor color1, AsciiColor color2);
AsciiTextColor mixAsciiTextColor(AsciiTextColor color1, AsciiTextColor color2);

// ��ȡ�ַ�������
int getStringLineCount(const std::string &str);
// ���н�ȡ�ַ���(line1-line2)
std::string interceptString(const std::string &str, int line1, int line2);
// ƴ���ַ���
std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs);

// ����ƥ��
std::vector<std::string> bracketMatch(const std::string &str,
                                      int layerCount = 1,
                                      char leftBracket = '[',
                                      char rightBracket = ']');

// ���������ݳ����ȡ������
Coord2d getCoord(int length, int width, double px, double py);

// ƽ�����������е�Ԫ�������ɸ���������
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