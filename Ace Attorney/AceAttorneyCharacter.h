#pragma once

#include "AnalyzeCommand.h"
#include <shared_mutex>

namespace AceAttorney {
class AceAttorneyGame;

// ��ɫ��
class AceAttorneyCharacter {
public:
  AceAttorneyCharacter() = default;
  AceAttorneyCharacter(const std::string &name, int age)
      : name(name), age(age) {
    game = nullptr;
  }

  // ����Ϸ
  void bind(AceAttorneyGame *game);

  // �Ƿ��
  bool isBind() const;

  // ������
  void chatBox(const AsciiBasicString &text, int speed = 10);
  // ����
  void objection();

  // ��ȡ����
  std::string getName() const { return name; }
  // ��ȡ����
  int getAge() const { return age; }
  // ��ȡ��Ϸָ��
  AceAttorneyGame *getGame() { return game; }

private:
  std::string name;
  int age;
  AceAttorneyGame *game;
  std::shared_mutex *s_mtx;
};

typedef std::vector<AceAttorneyCharacter> AceAttorneyCharaMngr;
} // namespace AceAttorney