#pragma once

#include "AceAttorneyChatbox.h"
#include "AceAttorneyObject.h"
#include <shared_mutex>

namespace AceAttorney {
class AceAttorneyGame;

// ��ɫ��
class AceAttorneyCharacter : public AceAttorneyObject {
public:
  using pSharedMutex = std::shared_ptr<std::shared_mutex>;

  AceAttorneyCharacter(pGame game);
  AceAttorneyCharacter(const std::string &name, int age);

  // ��
  void bind(pGame game) override;
  // ������
  void chatBox(const AsciiBasicString &text, int speed = 20);
  // ����
  void objection();

  // ��ȡ����
  std::string getName() const { return name; }
  // ��ȡ����
  int getAge() const { return age; }

private:
  std::string name;
  int age;
};

typedef std::vector<AceAttorneyCharacter> AceAttorneyCharaMngr;
} // namespace AceAttorney