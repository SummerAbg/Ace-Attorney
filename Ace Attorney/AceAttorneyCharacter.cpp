#include "AceAttorneyCharacter.h"
#include "AceAttorneyGame.h"

AceAttorney::AceAttorneyCharacter::AceAttorneyCharacter(pGame game)
    : AceAttorneyObject(game) {
  this->name = "null";
  this->age = 0;
}

AceAttorney::AceAttorneyCharacter::AceAttorneyCharacter(const std::string &name,
                                                        int age)
    : AceAttorneyObject(nullptr), name(name), age(age) {}

void AceAttorney::AceAttorneyCharacter::bind(pGame game) {
  AceAttorneyObject::bind(game);
}

void AceAttorney::AceAttorneyCharacter::chatBox(const AsciiBasicString &text,
                                                int speed) {
  if (!isBind()) {
    gameLog->log("�ý�ɫ��δ��!", __LINE__, __FILE__);
    return;
  }
  chatbox->setTitle(name);
  chatbox->setSpeed(speed);
  chatbox->outputText(text);
}

void AceAttorney::AceAttorneyCharacter::objection() {
  if (!isBind()) {
    return;
  }
  audioEngine->play2D("Objection!.wav");
  chatBox({"���h����!", false, {ASCII_COLOR_RED, {0, 0, 0, 0.0}}}, 5);
  std::this_thread::sleep_for(std::chrono::seconds(1));
}