#include "at_Tools.h"

namespace AsciiTools {
AsciiBasicString::AsciiBasicString(const char *str, bool trprState,
                                   const AsciiTextColor clr) {
  const std::string text = str;
  const AsciiTrprData trpr(text.size(), trprState);
  const AsciiTextColorData color(text.size(), clr);

  *this = AsciiBasicString(str, color, trpr);
}

AsciiBasicString::AsciiBasicString(const std::string &str, bool trprState,
                                   const AsciiTextColor clr) {
  *this = AsciiBasicString(str.c_str(), trprState, clr);
}

AsciiBasicString::AsciiBasicString(const char *str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr) {
  const std::string text = str;

  for (int i = 0; i < text.size(); i++) {
    const AsciiBasicChar chr = {text[i], clr[i], trpr[i]};

    this->text.emplace_back(chr);
  }
}

AsciiBasicString::AsciiBasicString(const std::string &str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr) {
  *this = AsciiBasicString(str.c_str(), clr, trpr);
}

AsciiBasicString::AsciiBasicString(const AsciiBasicChar &chr) {
  text.emplace_back(chr);
}

void AsciiBasicString::info() const {
  std::cout << "AsciiBasicString¶ÔÏó" << std::endl;
  std::cout << "Size:" << text.size() << std::endl;
  std::cout << "trprData:";
  for (const auto &index : text) {
    std::cout << index.isTrpr();
  }
  std::cout << std::endl;
}

bool AsciiBasicString::operator==(const AsciiBasicString &str) const {
  return this->text == Text(str.begin(), str.end()) ? true : false;
}

bool AsciiBasicString::operator!=(const AsciiBasicString &str) const {
  return !(*this == str);
}

AsciiBasicString AsciiBasicString::operator+=(const AsciiBasicString &str) {
  *this = *this + str;
  return *this;
}

AsciiBasicString AsciiBasicString::operator+=(const AsciiBasicChar &chr) {
  this->text.emplace_back(chr);
  return *this;
}

AsciiBasicString
AsciiBasicString::operator+(const AsciiBasicString &str) const {
  const std::string text = this->toString() + str.toString();
  const AsciiTrprData obj_Trpr = str.getTrprData();
  const AsciiTextColorData obj_clr = str.getTextColorData();

  AsciiTrprData trpr = this->getTrprData();
  AsciiTextColorData color = this->getTextColorData();

  trpr.insert(trpr.end(), obj_Trpr.begin(), obj_Trpr.end());
  color.insert(color.end(), obj_clr.begin(), obj_clr.end());

  const AsciiBasicString ret(text, color, trpr);

  return ret;
}

AsciiBasicString AsciiBasicString::operator+(const AsciiBasicChar &chr) const {
  AsciiBasicString ret = *this;
  ret.append(chr);
  return ret;
}

AsciiBasicChar &AsciiBasicString::operator[](int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  return text[index];
}

const AsciiBasicChar &AsciiBasicString::operator[](int index) const {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  return text[index];
}

void AsciiBasicString::del(int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  text.erase(text.begin() + index);
}

void AsciiBasicString::append(const AsciiBasicString &str) {
  for (const auto &index : str) {
    text.emplace_back(index);
  }
}

void AsciiBasicString::clear() {
  text.clear();
  text.shrink_to_fit();
}

std::string AsciiBasicString::toString() const {
  std::string ret;
  for (const auto &index : text) {
    ret += index.toString();
  }
  return ret;
}

AsciiTrprData AsciiBasicString::getTrprData() const {
  AsciiTrprData ret;
  for (const auto &index : text) {
    ret.emplace_back(index.isTrpr());
  }
  return ret;
}

AsciiTextColorData AsciiBasicString::getTextColorData() const {
  AsciiTextColorData ret;
  for (const auto &index : text) {
    ret.emplace_back(index.getColor());
  }
  return ret;
}

std::string AsciiBasicString::getSerializeStr() const {
  std::string ret;
  for (const auto &index : text) {
    ret += serializeType(index);
  }
  return ret;
}

void AsciiBasicString::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  for (const auto &index : tokens) {
    AsciiBasicChar chr;
    deserializeType(chr, index);
    this->text.emplace_back(chr);
  }
}

std::ostream &operator<<(std::ostream &output, const AsciiBasicString &str) {
  for (const auto &chr : str) {
    output << chr;
  }
  output << AsciiBasicChar('\0', AsciiBasicChar::getDefaultColor());
  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicString &str) {
  input >> str;
  input.ignore();
  return input;
}

AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr) {
  AsciiBasicString ret;
  for (int i = 0; i < TRPRSTR.size(); i++) {
    ret += chr;
  }
  return ret;
}

AsciiBasicString cutString(const AsciiBasicString &str, int index) {
  AsciiBasicString ret;
  for (int i = 0; i <= index; i++) {
    ret += str[i];
  }
  return ret;
}
AsciiBasicString overlapString(const AsciiBasicString &strA,
                               const AsciiBasicString &strB, int position,
                               bool isLimit) {
  AsciiBasicString ret = strA;

  const int size_str = (isLimit) ? strA.size() : strB.size();

  for (int i = 0; i < size_str; i++) {
    const int index = i + position;

    if (index < ret.size() && i < strB.size()) {
      ret[index] = strB[i];
    } else if (index >= ret.size() && i < strB.size()) {
      ret += strB[i];
    }
  }

  return ret;
}
} // namespace AsciiTools