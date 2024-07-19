#include "at_Debug.h"

void AsciiTools::debug_log(const std::string &str) {
  AsciiBasicString prefix = {
      "[ debug ]", false, {ASCII_COLOR_RED, ASCII_COLOR_YELLOW_GREEN}};
  AsciiBasicString log = prefix + " " + str;
  std::cout << log << std::endl;
}

void AsciiTools::WinAPIText(COORD coord, const std::string &str) {
  static std::string buffer;

  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hndl, coord);

  for (int i = 0; i < buffer.size(); i++) {
    std::cout << " ";
  }
  buffer = str;

  SetConsoleCursorPosition(hndl, coord);
  std::cout << str;
}