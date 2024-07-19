#include "at_Tools.h"

namespace AsciiTools {
AsciiColor::AsciiColor(int r, int g, int b, double a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

AsciiColor::AsciiColor(const std::string &str) {
  const auto tokens = split(str, ',');
  if (tokens.size() == paramCount_asciicolor) {
    r = stringToInt(tokens[0]);
    g = stringToInt(tokens[1]);
    b = stringToInt(tokens[2]);
    a = stringToDouble(tokens[3]);
  } else {
    throw AsciiBasicException(__FUNC__,
                              "str->rgba时发现字符串读取错误(tokens.size()!=" +
                                  std::to_string(paramCount_asciicolor) + ")");
  }
}

bool AsciiColor::operator==(AsciiColor color) const {
  return (this->r == color.r && this->g == color.g && this->b == color.b &&
          this->a == color.a)
             ? true
             : false;
}

bool AsciiColor::operator!=(AsciiColor color) const {
  return !(*this == color);
}

std::string AsciiColor::toString() const {
  return spliceString(",", r, g, b, a);
}
AsciiTextColor::AsciiTextColor(AsciiColor color_text,
                               AsciiColor color_background) {
  this->color_text = color_text;
  this->color_background = color_background;
}
AsciiTextColor::AsciiTextColor(const std::string &str) {
  const auto tokens = split(str, ',');
  if (tokens.size() == paramCount_asciitextcolor) {
    color_text.r = stringToInt(tokens[0]);
    color_text.g = stringToInt(tokens[1]);
    color_text.b = stringToInt(tokens[2]);
    color_text.a = stringToDouble(tokens[3]);
    color_background.r = stringToInt(tokens[4]);
    color_background.g = stringToInt(tokens[5]);
    color_background.b = stringToInt(tokens[6]);
    color_background.a = stringToDouble(tokens[7]);
  } else {
    throw AsciiBasicException(
        __FUNC__, "str->rgb时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_asciitextcolor) + ")");
  }
}
bool AsciiTextColor::operator==(AsciiTextColor color) const {
  return (this->color_text == color.color_text &&
          this->color_background == color.color_background)
             ? true
             : false;
}
bool AsciiTextColor::operator!=(AsciiTextColor color) const {
  return !((*this) == color);
}
std::string AsciiTextColor::toString() const {
  std::string str_text_color = color_text.toString();
  std::string str_background_color = color_background.toString();
  std::string ret = str_text_color + "," + str_background_color + ";";

  return ret;
}

std::ostream &operator<<(std::ostream &output, AsciiColor color) {
  setWordColor(color);
  output << color.toString();

  auto color_default = AsciiBasicChar::getDefaultColor();
  setWordColor(color_default.color_text);

  return output;
}

std::istream &operator>>(std::istream &input, AsciiColor color) {
  input >> color.r;
  input >> color.g;
  input >> color.b;
  input >> color.a;

  return input;
}

std::ostream &operator<<(std::ostream &output, AsciiTextColor color) {
  setWordColor(color.color_text);
  setBackgroundColor(color.color_background);
  output << color.toString();

  auto color_default = AsciiBasicChar::getDefaultColor();
  setBackgroundColor(color_default.color_background);
  setWordColor(color_default.color_text);

  return output;
}

std::istream &operator>>(std::istream &input, AsciiTextColor color) {
  input >> color.color_text;
  input >> color.color_background;

  return input;
}
} // namespace AsciiTools