#pragma once

#include "AceAttorneyCharacter.h"
// #include "TheadPool.h"

namespace AceAttorney {
// ��Ϸ��
class AceAttorneyGame {
public:
  AceAttorneyGame() = default;
  AceAttorneyGame(int length, int width);
  ~AceAttorneyGame();

  // ��ӽ�ɫ
  void addCharacter(AceAttorneyCharacter &chara);

  AsciiBasicLayerMngr *getScreen();
  ISoundEngine *getISoundEngine();

  // ��ȡ��Ϸ����
  int getLength() const { return length; }
  // ��ȡ��Ϸ���
  int getWidth() const { return width; }

  // ִ������
  void executeCommands(const std::vector<std::string> &commands);
  void executeCommands(const std::string &path);
  // ������Ϸ
  void run(const std::string &path);
  void run(const std::function<void()> &callback);

  std::shared_mutex *getSharedMutex() { return &s_mtx; }

private:
  void update();
  void display();
  void control();

private:
  void cmd_text(const Option &options);

private:
  int deltaTime;
  int length;
  int width;
  AsciiBasicLayerMngr *screen;
  ISoundEngine *audioEngine;
  AceAttorneyCharaMngr *charas;
  // ThreadPool *threadPool;
  int fps;
  std::shared_mutex s_mtx;
};
} // namespace AceAttorney