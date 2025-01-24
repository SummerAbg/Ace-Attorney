#include "AceAttorneyBasic.h"

Log *AceAttorney::gameLog = new Log(SpecificDisplay);

void AceAttorney::initAsciiGL() {
  AsciiBasicChar::setTrprChr(' ');
  AsciiBasicChar::setDefaultColor({ASCII_COLOR_WHITE, ASCII_COLOR_BLACK});
}

void AceAttorney::initWindowRGB() {
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);   // 输入句柄
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 输出句柄
  DWORD dwInMode, dwOutMode;
  GetConsoleMode(hIn, &dwInMode);   // 获取控制台输入模式
  GetConsoleMode(hOut, &dwOutMode); // 获取控制台输出模式
  dwInMode |= 0x0200;               // 更改
  dwOutMode |= 0x0004;
  SetConsoleMode(hIn, dwInMode);   // 设置控制台输入模式
  SetConsoleMode(hOut, dwOutMode); // 设置控制台输出模式
}

void AceAttorney::initWindow(int length, int width) {
  const std::wstring title = windowTitle + L" (" + std::to_wstring(length) +
                             L", " + std::to_wstring(width) + L")";
  setWindowSize(length * TRPRSTR.size(), width);
  setFont(30);
  SetConsoleTitle(title.c_str());
  AsciiGL::hideCursor();
}

int AceAttorney::getFPS(int deltaTime) {
  static int fps = 0;
  static int timeLeft = 1000; // 取固定时间间隔为1秒
  static int frameCount = 0;

  ++frameCount;
  timeLeft -= deltaTime;
  if (timeLeft < 0) {
    fps = frameCount;
    frameCount = 0;
    timeLeft = 1000;
  }
  return fps;
}

void AceAttorney::setFont(int size) {
  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof cfi;
  cfi.nFont = 0;
  cfi.dwFontSize.X = 0;
  cfi.dwFontSize.Y = size; // 设置字体大小
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = FW_NORMAL;                 // 字体粗细 FW_BOLD
  wcscpy_s(cfi.FaceName, windowFont.c_str()); // 设置字体，必须是控制台已有的
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void AceAttorney::setWindowSize(int length, int width) {
  char command[64];
  sprintf_s(command, "mode con cols=%d lines=%d", length, width);
  system(command);
}

std::string AceAttorney::readFile(const std::string &path) {
  std::fstream reader(path);
  std::string fileData;

  if (!reader.is_open()) {
    gameLog->log("无法正常打开文件!", __LINE__, __FILE__);
    exit(-1);
  }

  std::string buffer;
  while (std::getline(reader, buffer)) {
    fileData += buffer + "\n";
  }
  reader.close();
  return fileData;
}