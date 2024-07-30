#include "at_Tools.h"

namespace AsciiTools {
AsciiBasicString::AsciiBasicString() { text = std::make_shared<Text>(); }

AsciiBasicString::AsciiBasicString(const char *str, bool trprState,
                                   const AsciiTextColor clr) {
  text = std::make_shared<Text>();
  const std::string text = str;
  const AsciiTrprData trpr(text.size(), trprState);
  const AsciiTextColorData color(text.size(), clr);

  *this = AsciiBasicString(str, color, trpr);
}

AsciiBasicString::AsciiBasicString(const std::string &str, bool trprState,
                                   const AsciiTextColor clr) {
  text = std::make_shared<Text>();
  *this = AsciiBasicString(str.c_str(), trprState, clr);
}

AsciiBasicString::AsciiBasicString(const char *str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr) {
  this->text = std::make_shared<Text>();
  const std::string text = str;

  for (int i = 0; i < text.size(); i++) {
    const AsciiBasicChar chr = {text[i], clr[i], trpr[i]};

    this->text->emplace_back(chr);
  }
}

AsciiBasicString::AsciiBasicString(const std::string &str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr) {
  text = std::make_shared<Text>();
  *this = AsciiBasicString(str.c_str(), clr, trpr);
}

AsciiBasicString::AsciiBasicString(const AsciiBasicChar &chr) {
  this->text = std::make_shared<Text>();
  text->emplace_back(chr);
}

AsciiBasicString::AsciiBasicString(const AsciiBasicString &str) {
  text = std::make_shared<Text>(*str.text);
}

AsciiBasicString::AsciiBasicString(AsciiBasicString &&str) noexcept {
  text = str.text;
  str.text = nullptr;
}

void AsciiBasicString::info() const {
  std::cout << "AsciiBasicString¶ÔÏó" << std::endl;
  std::cout << "size:" << text->size() << std::endl;
  std::cout << "trprData:";
  for (const auto &index : *text) {
    std::cout << index.isTrpr();
  }
  std::cout << std::endl;
  std::cout << "colorData:";
  for (const auto &index : *text) {
    std::cout << index.getColor() << "^^^";
  }
  std::cout << std::endl;
}

bool AsciiBasicString::operator==(const AsciiBasicString &str) const {
  return *this->text == *str.text ? true : false;
}

bool AsciiBasicString::operator==(AsciiBasicString &&str) const noexcept {
  bool ret = *this->text == *str.text ? true : false;
  str.text = nullptr;

  return ret;
}

bool AsciiBasicString::operator!=(const AsciiBasicString &str) const {
  return !(*this == str);
}

bool AsciiBasicString::operator!=(AsciiBasicString &&str) const noexcept {
  return !(*this == std::move(str));
}

AsciiBasicString &AsciiBasicString::operator+=(const AsciiBasicString &str) {
  append(str);

  return *this;
}

AsciiBasicString &
AsciiBasicString::operator+=(AsciiBasicString &&str) noexcept {
  append(std::move(str));

  return *this;
}

AsciiBasicString &AsciiBasicString::operator+=(const AsciiBasicChar &chr) {
  append(chr);

  return *this;
}

AsciiBasicString
AsciiBasicString::operator+(const AsciiBasicString &str) const {
  const AsciiBasicString ret;

  ret.text->insert(ret.text->end(), this->text->begin(), this->text->end());
  ret.text->insert(ret.text->end(), str.text->begin(), str.text->end());

  return ret;
}

AsciiBasicString AsciiBasicString::operator+(const AsciiBasicChar &chr) const {
  AsciiBasicString ret = *this;
  ret.append(chr);

  return ret;
}

AsciiBasicChar &AsciiBasicString::operator[](int index) {
  if (index < 0 || index >= text->size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  return (*text)[index];
}

const AsciiBasicChar &AsciiBasicString::operator[](int index) const {
  if (index < 0 || index >= text->size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  return (*text)[index];
}

AsciiBasicString &AsciiBasicString::operator=(const AsciiBasicString &str) {
  *text = *str.text;

  return *this;
}

AsciiBasicString &AsciiBasicString::operator=(AsciiBasicString &&str) noexcept {
  this->text = str.text;
  str.text = nullptr;

  return *this;
}

void AsciiBasicString::del(int index) {
  if (index < 0 || index >= text->size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  text->erase(text->begin() + index);
}

void AsciiBasicString::append(const AsciiBasicString &str) {
  for (const auto &index : str) {
    text->emplace_back(index);
  }
}

void AsciiBasicString::append(const AsciiBasicChar &chr) {
  text->emplace_back(chr);
}

void AsciiBasicString::append(AsciiBasicChar &&chr) noexcept {
  text->emplace_back(chr);
}

void AsciiBasicString::append(AsciiBasicString &&str) noexcept {
  for (auto &&index : str) {
    text->emplace_back(index);
  }
  str.text = nullptr;
}

void AsciiBasicString::clear() {
  text->clear();
  text->shrink_to_fit();
}

std::string AsciiBasicString::toString() const {
  std::string ret;
  for (const auto &index : *text) {
    ret += index.toString();
  }
  return ret;
}

AsciiTrprData AsciiBasicString::getTrprData() const {
  AsciiTrprData ret;
  for (const auto &index : *text) {
    ret.emplace_back(index.isTrpr());
  }
  return ret;
}

AsciiTextColorData AsciiBasicString::getTextColorData() const {
  AsciiTextColorData ret;
  for (const auto &index : *text) {
    ret.emplace_back(index.getColor());
  }
  return ret;
}

std::string AsciiBasicString::getSerializeStr() const {
  std::string ret;
  for (const auto &index : *text) {
    ret += serializeType(index);
  }
  return ret;
}

void AsciiBasicString::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  for (const auto &index : tokens) {
    AsciiBasicChar chr;
    deserializeType(chr, index);
    this->text->emplace_back(chr);
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