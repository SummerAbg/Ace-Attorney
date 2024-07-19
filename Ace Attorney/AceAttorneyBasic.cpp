#include "AceAttorneyBasic.h"

Log *AceAttorney::gameLog = new Log(SimpleDisplay);

void AceAttorney::initAsciiGL() {
  AsciiBasicChar::setTrprChr('\\');
  AsciiBasicChar::setDefaultColor({ASCII_COLOR_WHITE, ASCII_COLOR_BLACK});
}

void AceAttorney::initWindowRGB() {
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);   // ������
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ������
  DWORD dwInMode, dwOutMode;
  GetConsoleMode(hIn, &dwInMode);   // ��ȡ����̨����ģʽ
  GetConsoleMode(hOut, &dwOutMode); // ��ȡ����̨���ģʽ
  dwInMode |= 0x0200;               // ����
  dwOutMode |= 0x0004;
  SetConsoleMode(hIn, dwInMode);   // ���ÿ���̨����ģʽ
  SetConsoleMode(hOut, dwOutMode); // ���ÿ���̨���ģʽ
}

void AceAttorney::initWindow(int length, int width) {
  const std::wstring title = windowTitle + L"(" + std::to_wstring(length) +
                             L", " + std::to_wstring(width) + L")";
  setWindowSize(length * TRPRSTR.size(), width);
  setFont(30);
  SetConsoleTitle(title.c_str());
  hideCursor();
}

/* double AceAttorney::getFPS() {
  static double fps = 0.0;
  static int frameCount = 0;
  static auto lastTime = std::chrono::system_clock::now();
  static auto curTime = std::chrono::system_clock::now();

  curTime = std::chrono::system_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(curTime - lastTime);
  double duration_s = double(duration.count()) *
                      std::chrono::microseconds::period::num /
                      std::chrono::microseconds::period::den;

  if (duration_s > 2) // 2��֮��ʼͳ��FPS
  {
    fps = frameCount / duration_s;
    frameCount = 0;
    lastTime = curTime;
  }

  ++frameCount;

  return fps;
}*/
int AceAttorney::getFPS(int deltaTime) {
  static int fps = 0;
  static int timeLeft = 100; // ȡ�̶�ʱ����Ϊ0.1��
  static int frameCount = 0;

  ++frameCount;
  timeLeft -= deltaTime;
  if (timeLeft < 0) {
    fps = frameCount;
    frameCount = 0;
    timeLeft = 100;
  }
  return fps;
}

void AceAttorney::setFont(int size) {
  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof cfi;
  cfi.nFont = 0;
  cfi.dwFontSize.X = 0;
  cfi.dwFontSize.Y = size; // ���������С
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = FW_NORMAL;                 // �����ϸ FW_BOLD
  wcscpy_s(cfi.FaceName, windowFont.c_str()); // �������壬�����ǿ���̨���е�
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
    gameLog->log("�޷��������ļ�!");
    exit(-1);
  }

  std::string buffer;
  while (std::getline(reader, buffer)) {
    fileData += buffer + "\n";
  }
  reader.close();
  return fileData;
}