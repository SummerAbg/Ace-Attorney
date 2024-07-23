#include "at_BasicChar.h"
#include "at_Tools.h"

namespace AsciiTools {
char AsciiBasicChar::trprChr = ' ';
AsciiTextColor AsciiBasicChar::default_clr = {ASCII_COLOR_WHITE,
                                              ASCII_COLOR_BLACK};

std::ostream &operator<<(std::ostream &output, const AsciiBasicChar &chr) {
  static AsciiBasicChar buffer_chr;

  if (chr.getColor() != buffer_chr.getColor()) {
    setWordColor(chr.color.color_text);
    setBackgroundColor(chr.color.color_background);
  }

  if (!chr.trprState) {
    output << chr.character;
  } else {
    output << AsciiBasicChar::trprChr;
  }

  buffer_chr = chr;

  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicChar &chr) {
  input >> chr.character;
  input >> chr.color;
  input >> chr.trprState;
  return input;
}

void AsciiBasicChar::info() const {
  std::cout << "AsciiBasicChar¶ÔÏó" << std::endl;
  std::cout << "character:" << character << std::endl
            << "trprState:" << trprState << std::endl;
}

std::string AsciiBasicChar::toString() const {
  return std::string(1, character);
}

bool AsciiBasicChar::operator==(const AsciiBasicChar &chr) const {
  return (character == chr.getChr() && trprState == chr.isTrpr() &&
          color == chr.getColor())
             ? true
             : false;
}

bool AsciiBasicChar::operator!=(const AsciiBasicChar &chr) const {
  return !(*this == chr);
}

void AsciiBasicChar::setTrprChr(char chr) { trprChr = chr; }

char AsciiBasicChar::getTrprChr() { return trprChr; }

void AsciiBasicChar::setDefaultColor(AsciiTextColor clr) { default_clr = clr; }

AsciiTextColor AsciiBasicChar::getDefaultColor() { return default_clr; }

std::string AsciiBasicChar::getSerializeStr() const {
  return serializeType(character, trprState, color);
}

void AsciiBasicChar::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() != 3) {
    throw AsciiBasicException(__FUNC__, FileFormatError);
  }

  deserializeType(character, tokens[0]);
  deserializeType(trprState, tokens[1]);
  deserializeType(color, tokens[2]);
}
} // namespace AsciiTools