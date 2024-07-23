#pragma once

#include "at_Basic.h"
#include "at_BasicObject.h"
#include "at_TextColor.h"

namespace AsciiTools {
// 基本字符类
class AsciiBasicChar : public AsciiBasicObject {
public:
  // 构造基本字符
  AsciiBasicChar() = default;
  AsciiBasicChar(char chr, bool trprState = false)
      : character(chr), color(getDefaultColor()), trprState(trprState) {}
  AsciiBasicChar(char chr, AsciiTextColor clr, bool trprState = false)
      : character(chr), color(clr), trprState(trprState) {}

  // 输出信息
  void info() const;
  // AsciiBasicChar转换为std::string
  std::string toString() const;

  bool operator==(const AsciiBasicChar &chr) const;
  bool operator!=(const AsciiBasicChar &chr) const;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicChar &chr);

  friend std::istream &operator>>(std::istream &input, AsciiBasicChar &chr);

  // 设置透明字符
  static void setTrprChr(char chr);
  // 获取透明字符
  static char getTrprChr();
  // 设置默认颜色
  static void setDefaultColor(AsciiTextColor clr);
  // 获取默认颜色
  static AsciiTextColor getDefaultColor();

  // 获取字符
  char getChr() const { return character; }
  // 设置字符
  void setChr(char chr) { character = chr; }
  // 获取透明状态
  bool isTrpr() const { return trprState; }
  // 设置透明
  void setTrpr(bool trprState) { this->trprState = trprState; }
  // 获取颜色
  AsciiTextColor getColor() const { return color; }
  // 设置颜色
  void setColor(AsciiTextColor clr) { color = clr; }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  char character;       // 字符
  bool trprState;       // 透明状态
  AsciiTextColor color; // 颜色

  static char trprChr;               // 透明字符(透明时填充的字符)
  static AsciiTextColor default_clr; // 默认颜色
};
} // namespace AsciiTools