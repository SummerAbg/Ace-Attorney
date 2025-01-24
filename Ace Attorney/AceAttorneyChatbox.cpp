#include "AceAttorneyChatbox.h"
#include "AceAttorneyGame.h"

AceAttorney::AceAttorneyChatbox::AceAttorneyChatbox()
    : AceAttorneyObject(nullptr), speed(0) /*, layer_chatbox(nullptr)*/ {}

AceAttorney::AceAttorneyChatbox::AceAttorneyChatbox(pGame game)
    : AceAttorneyObject(game), speed(0) /*, layer_chatbox(nullptr)*/ {}

AceAttorney::AceAttorneyChatbox::AceAttorneyChatbox(int length, int width,
                                                    pGame game)
    : AceAttorneyObject(game), speed(0) /*, layer_chatbox(nullptr) */ {}

AceAttorney::AceAttorneyChatbox::~AceAttorneyChatbox() {
  if (!isBind()) {
    gameLog->log("该角色还未绑定!", __LINE__, __FILE__);
    return;
  }
  std::cout << (bool)screen << std::endl;
  // screen->deleteLayer(name_layer);
}

void AceAttorney::AceAttorneyChatbox::initChatBox(int speed,
                                                  const std::string &title) {
  if (!isBind()) {
    gameLog->log("该角色还未绑定!", __LINE__, __FILE__);
    return;
  }

  this->speed = speed;
  // 通过canvas_chatbox存储聊天箱的画布信息
  // 并使用getChatBoxCanvas()函数初始化画布的大小等信息
  auto canvas_chatbox = getChatBoxCanvas(*game);

  // appendChatBoxLayer()通过canvas_chatbox对象以在screen中添加聊天箱图层
  appendChatBoxLayer(canvas_chatbox, title, *game, *screen);
  // 通过layer_chatbox指针对象来更加方便地操作screen中的聊天箱图层
  //*this->layer_chatbox = screen->getLayer(name_layer);
}

void AceAttorney::AceAttorneyChatbox::outputText(
    const AsciiTools::AsciiBasicString &text) {
  if (!isBind()) {
    gameLog->log("该角色还未绑定!", __LINE__, __FILE__);
    return;
  }

  {
    std::unique_lock<std::shared_mutex> lock(*s_mtx);
    (*screen)[name_layer].setDisplayState(true);
    (*screen)["layer_chatbox_name"].setDisplayState(true);
    (*screen)["layer_chatbox"].setDisplayState(true);
  }
  auto str_text = text;
  for (int i = 0; i < text.size(); i++) {
    auto clr = str_text[i].getColor();
    // clr.color_background = clr_ChatBox_Text.color_background;
    clr.color_background = {0, 0, 0, 0.0};

    str_text[i].setColor(clr);
  }

  AsciiBasicString tmp_text;
  Vec2d coord_text = getCoord(game->getLength(), game->getWidth(), 0.1, 0.78);

  for (int i = 0; i < text.size(); i++) {
    tmp_text += str_text[i];
    {
      // std::unique_lock<std::shared_mutex> lock(*s_mtx);
      setText(*screen, coord_text, tmp_text, name_layer);
    }
    audioEngine->play2D("se003.wav");
    std::this_thread::sleep_for(std::chrono::milliseconds(speed));
  }
  _getch();
  {
    std::unique_lock<std::shared_mutex> lock(*s_mtx);
    // 此处需要将layer_chatbox_text，layer_chatbox，layer_chatbox_name的显示状态设置为false
    (*screen)[name_layer].setDisplayState(false);
    (*screen)["layer_chatbox_name"].setDisplayState(false);
    (*screen)["layer_chatbox"].setDisplayState(false);
  };
}

void AceAttorney::AceAttorneyChatbox::setTitle(const std::string &title) {
  // 由于图层组的逻辑没有实现，所以暂且采用以下代码
  if (screen->isExistLayer("layer_chatbox_name")) {
    const int chatbox_x = 0;
    const int chatbox_y = static_cast<int>(game->getWidth() * goldenRatio);

    Coord2d coord_chatbox(chatbox_x, chatbox_y);
    AsciiBasicString str_title = {title, false, clr_ChatBox_Name};

    setText(*screen, coord_chatbox, str_title, "layer_chatbox_name");
  } else {
    gameLog->log("不存在layer_chatbox_name图层！", __LINE__, __FILE__);
  }
}