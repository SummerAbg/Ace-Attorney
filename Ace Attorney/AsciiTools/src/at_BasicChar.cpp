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
  std::string ret;
  ret += std::string(1, character) + ";";
  ret += std::to_string(trprState) + ";";
  ret += color.toString() + ";";
  /* ret = spliceString(";", {std::string(1, character),
                                std::to_string(trprState),
                        color.toString()});*/
  return ret;
}

void AsciiBasicChar::loadSerializeStr(const std::string &str) {
  auto tokens = split(str, ';');

  if (tokens.size() != 3) {
    throw AsciiBasicException(__FUNC__, FileFormatError);
  }

  this->character = str[0];
  this->trprState = stringToBool(tokens[1]);
  color = AsciiTextColor(tokens[2]);
}
} // namespace AsciiTools