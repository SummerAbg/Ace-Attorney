#pragma once

#include "at_BasicChar.h"

namespace AsciiTools {
// 基本字符串类
class AsciiBasicString : public AsciiBasicObject {
public:
  using Text = std::vector<AsciiBasicChar>;

  // 构造基本字符串
  AsciiBasicString() = default;
  AsciiBasicString(
      const char *str, bool isTrpr = false,
      const AsciiTextColor clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(
      const std::string &str, bool isTrpr = false,
      const AsciiTextColor clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(const char *str, const AsciiTextColorData &clr,
                   const AsciiTrprData &trpr);
  AsciiBasicString(const std::string &str, const AsciiTextColorData &clr,
                   const AsciiTrprData &trpr);
  AsciiBasicString(const AsciiBasicChar &chr);

  // 输出信息
  void info() const;
  // AsciiBasicString转换为std::string
  std::string toString() const;

  // 获取头尾地址的函数(为了能够使用c++11的新特性)
  auto begin() const { return text.begin(); }
  auto end() const { return text.end(); }

  // 基本运算符
  bool operator==(const AsciiBasicString &str) const;
  bool operator!=(const AsciiBasicString &str) const;

  AsciiBasicString operator+=(const AsciiBasicString &str);
  AsciiBasicString operator+=(const AsciiBasicChar &chr);
  AsciiBasicString operator+(const AsciiBasicString &str) const;
  AsciiBasicString operator+(const AsciiBasicChar &chr) const;

  AsciiBasicChar &operator[](int index);
  const AsciiBasicChar &operator[](int index) const;

  /////////////////////////////////////////////////////////////

  // 在指定位置插入字符/字符串
  // void insert(int index, const AsciiBasicString &str);
  // void insert(int index, const AsciiBasicChar &chr);

  // 删除字符串指定位置的字符
  void del(int index);
  // 给字符串的末尾添加字符
  void append(const AsciiBasicChar &chr) { text.emplace_back(chr); }
  void append(const AsciiBasicString &str);
  // 清空字符串
  void clear();

  // 获取字符串大小
  int size() const { return static_cast<int>(text.size()); }

  // 获取透明数据
  AsciiTrprData getTrprData() const;
  // 获取颜色数据
  AsciiTextColorData getTextColorData() const;

  // 重载输出运算符
  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicString &str);
  // 重载输入运算符
  friend std::istream &operator>>(std::istream &input, AsciiBasicString &str);

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  Text text; // 字符容器
};

const AsciiBasicString TRPRSTR = {
    "  ", true, {ASCII_COLOR_GREY, ASCII_COLOR_BLACK}};

// 获取自适应字符串
AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr);

// 剪裁字符串(获取index位置及之前的字符串)
AsciiBasicString cutString(const AsciiBasicString &str, int index);

// 重叠字符串
// 将strB重叠在strA的position的位置上
// 当isLimit为true时，得到的字符串大小以strA为标准
// 如:
//    ①当strA的长度大于strB的长度且处于非限定模式下:
//      "egg"重叠在"apple"的0位置上，得到"eggle"
//    ②当strA的长度小于strB的长度且处于非限定模式下:
//      "apple"重叠在"egg"的0位置上，得到"apple"
//    ③当strA的长度小于strB的长度且处于限定模式下:
//      "apple"重叠在"egg"的0位置上，得到"app"
AsciiBasicString overlapString(const AsciiBasicString &strA,
                               const AsciiBasicString &strB, int psotion = 0,
                               bool isLimit = false);
} // namespace AsciiTools