#pragma once

#include "AceAttorneyChatbox.h"
#include "AceAttorneyObject.h"
#include <shared_mutex>

namespace AceAttorney {
class AceAttorneyGame;

// 角色类
class AceAttorneyCharacter : public AceAttorneyObject {
public:
  using pSharedMutex = std::shared_ptr<std::shared_mutex>;

  AceAttorneyCharacter(pGame game);
  AceAttorneyCharacter(const std::string &name, int age);

  // 绑定
  void bind(pGame game) override;
  // 聊天箱
  void chatBox(const AsciiBasicString &text, int speed = 20);
  // 异议
  void objection();

  // 获取名字
  std::string getName() const { return name; }
  // 获取年龄
  int getAge() const { return age; }

private:
  std::string name;
  int age;
};

typedef std::vector<AceAttorneyCharacter> AceAttorneyCharaMngr;
} // namespace AceAttorney