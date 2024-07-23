#pragma once

#include "at_BasicObject.h"
#include <iostream>

namespace AsciiTools {
// AsciiColor参数个数
const int paramCount_asciicolor = 4;

// AsciiTextColor参数个数
const int paramCount_asciitextcolor = 2;

// RGBA颜色
struct AsciiColor : public AsciiBasicObject {
  int r;
  int g;
  int b;
  double a;

  AsciiColor() = default;
  AsciiColor(int r, int g, int b, double a = 1.0);
  AsciiColor(const std::string &str);

  bool operator==(AsciiColor color) const;
  bool operator!=(AsciiColor color) const;

  friend std::ostream &operator<<(std::ostream &output, AsciiColor color);
  friend std::istream &operator>>(std::istream &input, AsciiColor color);

  void info() const;
  std::string toString() const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);
};

// 文本颜色
struct AsciiTextColor : public AsciiBasicObject {
  AsciiColor color_text;
  AsciiColor color_background;

  AsciiTextColor() = default;
  AsciiTextColor(AsciiColor color_text, AsciiColor color_background);
  AsciiTextColor(const std::string &str);

  bool operator==(AsciiTextColor color) const;
  bool operator!=(AsciiTextColor color) const;

  friend std::ostream &operator<<(std::ostream &output, AsciiTextColor color);
  friend std::istream &operator>>(std::istream &input, AsciiTextColor color);

  void info() const;
  std::string toString() const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);
};

const AsciiColor ASCII_COLOR_RED = {255, 0, 0};
const AsciiColor ASCII_COLOR_ORANGE = {255, 128, 0};
const AsciiColor ASCII_COLOR_YELLOW = {255, 255, 0};
const AsciiColor ASCII_COLOR_YELLOW_GREEN = {128, 255, 0};
const AsciiColor ASCII_COLOR_GREEN = {0, 255, 0};
const AsciiColor ASCII_COLOR_CYAN_GREEN = {0, 255, 128};
const AsciiColor ASCII_COLOR_CYAN = {0, 255, 255};
const AsciiColor ASCII_COLOR_INDIGO = {0, 128, 255};
const AsciiColor ASCII_COLOR_BLUE = {0, 0, 255};
const AsciiColor ASCII_COLOR_PURPLE = {128, 0, 255};
const AsciiColor ASCII_COLOR_MAGENTA = {255, 0, 255};
const AsciiColor ASCII_COLOR_PURPLE_RED = {255, 0, 128};

const AsciiColor ASCII_COLOR_GREY = {128, 128, 128};
const AsciiColor ASCII_COLOR_BLACK = {0, 0, 0};
const AsciiColor ASCII_COLOR_WHITE = {255, 255, 255};
} // namespace AsciiTools