#include "at_TypeConvert.h"

namespace AsciiTools {
int stringToInt(const std::string &str) { return atoi(str.c_str()); }

int charToInt(char chr) { return atoi(std::string(1, chr).c_str()); }

bool charToBool(char chr) { return intToBool(charToInt(chr)); }

bool stringToBool(const std::string &str) {
  if (str == "true") {
    return true;
  } else if (str == "false") {
    return false;
  } else {
    throw AsciiBasicException(__FUNC__, "str非法!(只能是true或false!)");
  }
}

bool intToBool(int number) { return static_cast<bool>(number); }

double stringToDouble(const std::string &str) { return std::stod(str); }

short stringToShort(const std::string &str) {
  short *ret = reinterpret_cast<short *>(const_cast<char *>(str.c_str()));
  return *ret;
}
} // namespace AsciiTools