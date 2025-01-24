#pragma once

#include "AceAttorneyCharacter.h"
// #include "TheadPool.h"

namespace AceAttorney {
// ��Ϸ��
class AceAttorneyGame {
public:
  using pScreen = std::shared_ptr<AsciiGL::AsciiBasicLayerMngr>;
  using pCharaMngr = std::shared_ptr<AceAttorneyCharaMngr>;
  using pSharedMutex = std::shared_ptr<std::shared_mutex>;
  using pChatBox = std::shared_ptr<AceAttorneyChatbox>;

  AceAttorneyGame();
  explicit AceAttorneyGame(int length, int width);
  explicit AceAttorneyGame(const AceAttorneyGame &game);
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

  pSharedMutex getSharedMutex() { return s_mtx; }
  pChatBox getChatBox() { return chatbox; }

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
  pChatBox chatbox;

private:
  std::atomic_int deltaTime;
  std::atomic_int fps;
  int length;
  int width;
  pSharedMutex s_mtx;
};

// ��ȡ�����仭��
AsciiGL::AsciiBasicCanvas getChatBoxCanvas(AceAttorneyGame &game);

// ���������ͼ��
void appendChatBoxLayer(const AsciiGL::AsciiBasicCanvas &canvas,
                        const std::string &name, AceAttorneyGame &game,
                        AsciiGL::AsciiBasicLayerMngr &mngr);
} // namespace AceAttorney