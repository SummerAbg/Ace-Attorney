#include "AceAttorneyCharacter.h"
#include "AceAttorneyGame.h"

void AceAttorney::AceAttorneyCharacter::bind(AceAttorneyGame *game) {
  this->game = game;
}

bool AceAttorney::AceAttorneyCharacter::isBind() const {
  return game != nullptr ? true : false;
}

void AceAttorney::AceAttorneyCharacter::chatBox(const AsciiBasicString &text,
                                                int speed) {
  if (!isBind()) {
    gameLog->log("该角色还未绑定!");
    exit(-1);
  }
  AceAttorneyGame::pScreen screen = nullptr;
  irrklang::ISoundEngine *audioEngine = nullptr;
  auto *s_mtx = game->getSharedMutex();
  {
    std::shared_lock<std::shared_mutex> lock(*s_mtx);
    screen = game->getScreen();
    audioEngine = game->getISoundEngine();
  }

  AsciiBasicString str_text = text;
  for (int i = 0; i < text.size(); i++) {
    auto clr = str_text[i].getColor();
    clr.color_background = clr_ChatBox_Text.color_background;

    str_text[i].setColor(clr);
  }

  auto canvas_chatbox = getChatBoxCanvas(*game);
  appendChatBoxLayer(canvas_chatbox, name, *game, *screen);

  AsciiBasicString tmp_text;
  Vec2d coord_text;
  {
    std::shared_lock<std::shared_mutex> lock(*s_mtx);
    coord_text = getCoord(game->getLength(), game->getWidth(), 0.1, 0.78);
  }
  for (int i = 0; i < text.size(); i++) {
    tmp_text += str_text[i];
    {
      std::unique_lock<std::shared_mutex> lock(*s_mtx);
      setText(*screen, coord_text, tmp_text, "layer_chatbox_text");
    }
    audioEngine->play2D("se003.wav");
    std::this_thread::sleep_for(std::chrono::milliseconds(speed));
  }
  _getch();
  {
    std::unique_lock<std::shared_mutex> lock(*s_mtx);
    (*screen)["layer_chatbox_name"].setDisplayState(false);
    (*screen)["layer_chatbox_text"].setDisplayState(false);
    (*screen)["layer_chatbox"].setDisplayState(false);
  };
}

void AceAttorney::AceAttorneyCharacter::objection() {
  if (!isBind()) {
    gameLog->log("该角色还未绑定!");
    exit(-1);
  }
  irrklang::ISoundEngine *audioEngine = game->getISoundEngine();
  audioEngine->play2D("yiyayi!.wav");
  chatBox("異議あり!");
  std::this_thread::sleep_for(std::chrono::seconds(1));
}