#pragma once

#include "AceAttorneyCharacter.h"
// #include "TheadPool.h"

namespace AceAttorney {
// 游戏类
class AceAttorneyGame {
public:
  using pScreen = std::shared_ptr<AsciiGL::AsciiBasicLayerMngr>;
  using pCharaMngr = std::shared_ptr<AceAttorneyCharaMngr>;

  AceAttorneyGame() = default;
  AceAttorneyGame(int length, int width);
  ~AceAttorneyGame();

  // 添加角色
  void addCharacter(AceAttorneyCharacter &chara);

  pScreen getScreen();
  irrklang::ISoundEngine *getISoundEngine();

  // 获取游戏长度
  int getLength() const { return length; }
  // 获取游戏宽度
  int getWidth() const { return width; }

  // 执行命令
  void executeCommands(const std::vector<std::string> &commands);
  void executeCommands(const std::string &path);
  // 运行游戏
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

// 获取聊天箱画布
AsciiGL::AsciiBasicCanvas getChatBoxCanvas(AceAttorneyGame &game);

// 添加聊天箱图层
void appendChatBoxLayer(const AsciiGL::AsciiBasicCanvas &canvas,
                        const std::string &name, AceAttorneyGame &game,
                        AsciiGL::AsciiBasicLayerMngr &mngr);
} // namespace AceAttorney