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
  AsciiBasicLayerMngr *screen = nullptr;
  ISoundEngine *audioEngine = nullptr;

  int chatBoxLength = 0;
  int chatBoxWidth = 0;
  {
    std::unique_lock<std::shared_mutex> lock(*game->getSharedMutex());
    screen = game->getScreen();
    audioEngine = game->getISoundEngine();

    chatBoxLength = game->getLength();
    chatBoxWidth = (double)game->getWidth() * (1.0 - goldenRatio);
  }
  /* auto screen = game->getScreen();
  auto audioEngine = game->getISoundEngine();

  const int chatBoxLength = game->getLength();
  const int chatBoxWidth = (double)game->getWidth() * (1.0 - goldenRatio);*/

  AsciiBasicString str_name = {name, false, clr_ChatBox_Name};
  AsciiBasicString str_text = text;
  for (int i = 0; i < text.size(); i++) {
    auto clr = str_text[i].getColor();
    clr.color_background = clr_ChatBox_Text.color_background;

    str_text[i].setColor(clr);
  }

  AsciiBasicCanvas canvas_chatbox(chatBoxLength, chatBoxWidth, str_ChatBox);
  setBorder(canvas_chatbox, str_ChatBox_Border);
  setLine(canvas_chatbox, Vec2d(0, 0), Vec2d(chatBoxLength - 1, 0), TRPRSTR);
  setLine(canvas_chatbox, Vec2d(0, 1), Vec2d(chatBoxLength - 1, 1),
          str_ChatBox_Border);

  const int chatbox_x = 0;
  int chatbox_y = 0;
  {
    std::unique_lock<std::shared_mutex> lock(*game->getSharedMutex());
    chatbox_y = (double)game->getWidth() * goldenRatio;
  }
  Coord2d coord_chatbox(chatbox_x, chatbox_y);

  AsciiBasicLayer layer_chatbox(canvas_chatbox, coord_chatbox, "layer_chatbox");

  {
    std::unique_lock<std::shared_mutex> lock(*game->getSharedMutex());
    if (!screen->isExistLayer("layer_chatbox")) {
      screen->appendLayer(layer_chatbox);
    } else {
      screen->setLayer(layer_chatbox, "layer_chatbox");
    }

    setText(*screen, coord_chatbox, str_name, "layer_chatbox_name");
  }
  AsciiBasicString tmp_text;

  for (int i = 0; i < text.size(); i++) {
    Vec2d coord_text = coord_chatbox(1, 2);
    tmp_text += str_text[i];

    {
      std::unique_lock<std::shared_mutex> lock(*game->getSharedMutex());
      setText(*screen, coord_text, tmp_text, "layer_chatbox_text");
      audioEngine->play2D("se003.wav");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(speed));
  }
  _getch();
  {
    std::unique_lock<std::shared_mutex> lock(*game->getSharedMutex());
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
  ISoundEngine *audioEngine = game->getISoundEngine();
  audioEngine->play2D("Objection!.wav");
  chatBox("Objection!");
  std::this_thread::sleep_for(std::chrono::seconds(1));
}