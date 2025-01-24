#include "AceAttorneyObject.h"
#include "AceAttorneyChatbox.h"
#include "AceAttorneyGame.h"

AceAttorney::AceAttorneyObject::AceAttorneyObject(pGame game) {
  if (game) {
    this->game = game;
    this->s_mtx = game->getSharedMutex();
    this->audioEngine = game->getISoundEngine();
    this->screen = game->getScreen();
    this->chatbox = game->getChatBox();
  }
}

AceAttorney::AceAttorneyObject::~AceAttorneyObject() {
  if (this->game) {
    this->audioEngine->drop();
  }
}

void AceAttorney::AceAttorneyObject::bind(pGame game) {
  if (game) {
    this->game = game;
    this->s_mtx = game->getSharedMutex();
    this->audioEngine = game->getISoundEngine();
    this->screen = game->getScreen();
    this->chatbox = game->getChatBox();
  }
}