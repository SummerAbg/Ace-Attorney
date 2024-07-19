#include "at_Tools.h"
#include "agl_Basic.h"

namespace AsciiTools {
void setWordColor(AsciiColor color) {
  printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setBackgroundColor(AsciiColor color) {
  printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);
}

AsciiColor mixAsciiColor(AsciiColor color1, AsciiColor color2) {
  AsciiColor ret;
  ret.a = (1.0 - ((1.0 - color1.a) * (1.0 - color2.a)));
  ret.r =
      (color1.r * color1.a + color2.r * color2.a * (1.0 - color1.a)) / ret.a;
  ret.g =
      (color1.g * color1.a + color2.g * color2.a * (1.0 - color1.a)) / ret.a;
  ret.b =
      (color1.b * color1.a + color2.b * color2.a * (1.0 - color1.a)) / ret.a;

  return ret;
}

AsciiTextColor mixAsciiTextColor(AsciiTextColor color1, AsciiTextColor color2) {
  AsciiTextColor ret;
  ret.color_text = mixAsciiColor(color1.color_text, color2.color_text);
  ret.color_background =
      mixAsciiColor(color1.color_background, color2.color_background);
  return ret;
}

std::vector<std::string> split(const std::string &str, char chr) {
  if (str == "")
    return std::vector<std::string>();

  std::vector<std::string> ret;
  std::vector<int> pos;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == chr)
      pos.emplace_back(i);
  }
  pos.insert(pos.begin(), -1);
  pos.insert(pos.end(), (int)str.size());
  for (int i = 0; i < pos.size() - 1; i++) {
    if ((pos[i] + 1) <= (pos[i + 1] - 1)) {
      ret.emplace_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
    }
  }

  return ret;
}

int stringToInt(const std::string &str) { return atoi(str.c_str()); }

int charToInt(char chr) { return atoi(std::string(1, chr).c_str()); }

bool charToBool(char chr) { return intToBool(charToInt(chr)); }

bool stringToBool(const std::string &str) {
  return intToBool(stringToInt(str));
}

bool intToBool(int number) { return static_cast<bool>(number); }

double stringToDouble(const std::string &str) { return std::stod(str); }

int getStringLineCount(const std::string &str) {
  int ret = static_cast<int>(split(str, '\n').size());
  return ret;
}

std::string interceptString(const std::string &str, int line1, int line2) {
  const auto &tokens = split(str, '\n');
  std::vector<std::string> strBlocks;

  if (line1 <= tokens.size() && line2 <= tokens.size() && line1 > 0 &&
      line2 > 0 && line1 < line2) {
    for (int i = line1 - 1; i < line2; i++) {
      strBlocks.emplace_back(tokens[i]);
    }
  }

  std::string ret;
  for (const auto &index : strBlocks) {
    ret += index + "\n";
  }
  return ret;
}
std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs) {
  std::string ret;
  for (const auto &index : strs) {
    ret += index;
    if (index != strs[strs.size() - 1])
      ret += str;
  }
  return ret;
}
} // namespace AsciiTools