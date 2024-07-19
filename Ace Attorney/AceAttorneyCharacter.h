#pragma once

#include "AnalyzeCommand.h"
#include <shared_mutex>

namespace AceAttorney {
class AceAttorneyGame;

// 角色类
class AceAttorneyCharacter {
public:
  AceAttorneyCharacter() = default;
  AceAttorneyCharacter(const std::string &name, int age)
      : name(name), age(age) {
    game = nullptr;
  }

  // 绑定游戏
  void bind(AceAttorneyGame *game);

  // 是否绑定
  bool isBind() const;

  // 聊天箱
  void chatBox(const AsciiBasicString &text, int speed = 10);
  // 异议
  void objection();

  // 获取名字
  std::string getName() const { return name; }
  // 获取年龄
  int getAge() const { return age; }
  // 获取游戏指针
  AceAttorneyGame *getGame() { return game; }

private:
  std::string name;
  int age;
  AceAttorneyGame *game;
  std::shared_mutex *s_mtx;
};

typedef std::vector<AceAttorneyCharacter> AceAttorneyCharaMngr;
} // namespace AceAttorney