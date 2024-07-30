#pragma once

#include "AceAttorneyCharacter.h"
// #include "TheadPool.h"

namespace AceAttorney {
// ��Ϸ��
class AceAttorneyGame {
public:
  using pScreen = std::shared_ptr<AsciiGL::AsciiBasicLayerMngr>;
  using pCharaMngr = std::shared_ptr<AceAttorneyCharaMngr>;

  AceAttorneyGame() = default;
  AceAttorneyGame(int length, int width);
  ~AceAttorneyGame();

  // ��ӽ�ɫ
  void addCharacter(AceAttorneyCharacter &chara);

  pScreen getScreen();
  irrklang::ISoundEngine *getISoundEngine();

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
  pScreen screen;
  irrklang::ISoundEngine *audioEngine;
  pCharaMngr charas;

private:
  std::atomic_int deltaTime;
  int length;
  int width;
  int fps;
  std::shared_mutex s_mtx;
};

// ��ȡ�����仭��
AsciiGL::AsciiBasicCanvas getChatBoxCanvas(AceAttorneyGame &game);

// ���������ͼ��
void appendChatBoxLayer(const AsciiGL::AsciiBasicCanvas &canvas,
                        const std::string &name, AceAttorneyGame &game,
                        AsciiGL::AsciiBasicLayerMngr &mngr);
} // namespace AceAttorney