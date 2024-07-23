#include "at_Tools.h"

namespace AsciiTools {
AsciiColor::AsciiColor(int r, int g, int b, double a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

AsciiColor::AsciiColor(const std::string &str) {
  try {
    loadSerializeStr(str);
  } catch (const AsciiBasicException &error) {
    throw AsciiBasicException(__FUNC__, error.what());
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

void AsciiColor::info() const {
  std::cout << "AsciiColor对象" << std::endl;
  std::cout << this->toString() << std::endl;
}

std::string AsciiColor::toString() const {
  return spliceString(",", r, g, b, a);
}

std::string AsciiColor::getSerializeStr() const {
  return serializeType(r, g, b, a);
}

void AsciiColor::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() != paramCount_asciicolor) {
    throw AsciiBasicException(__FUNC__,
                              "str->rgba时发现字符串读取错误(tokens.size()!=" +
                                  std::to_string(paramCount_asciicolor) + ")");
  }

  deserializeType(r, tokens[0]);
  deserializeType(g, tokens[1]);
  deserializeType(b, tokens[2]);
  deserializeType(a, tokens[3]);
}

AsciiTextColor::AsciiTextColor(AsciiColor color_text,
                               AsciiColor color_background) {
  this->color_text = color_text;
  this->color_background = color_background;
}

AsciiTextColor::AsciiTextColor(const std::string &str) {
  try {
    loadSerializeStr(str);
  } catch (const AsciiBasicException &error) {
    throw AsciiBasicException(__FUNC__, error.what());
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
void AsciiTextColor::info() const {
  std::cout << "AsciiTextColor对象" << std::endl;
  std::cout << this->toString() << std::endl;
}

std::string AsciiTextColor::toString() const {
  std::string ret = spliceString(",", color_text, color_background);

  return ret;
}

std::string AsciiTextColor::getSerializeStr() const {
  return serializeType(color_text, color_background);
}

void AsciiTextColor::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() == paramCount_asciitextcolor) {
    deserializeType(color_text, tokens[0]);
    deserializeType(color_background, tokens[1]);
  } else {
    throw AsciiBasicException(
        __FUNC__, "str->rgb时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_asciitextcolor) + ")");
  }
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