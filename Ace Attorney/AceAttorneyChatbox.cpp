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
    gameLog->log("�ý�ɫ��δ��!", __LINE__, __FILE__);
    return;
  }
  std::cout << (bool)screen << std::endl;
  // screen->deleteLayer(name_layer);
}

void AceAttorney::AceAttorneyChatbox::initChatBox(int speed,
                                                  const std::string &title) {
  if (!isBind()) {
    gameLog->log("�ý�ɫ��δ��!", __LINE__, __FILE__);
    return;
  }

  this->speed = speed;
  // ͨ��canvas_chatbox�洢������Ļ�����Ϣ
  // ��ʹ��getChatBoxCanvas()������ʼ�������Ĵ�С����Ϣ
  auto canvas_chatbox = getChatBoxCanvas(*game);

  // appendChatBoxLayer()ͨ��canvas_chatbox��������screen�����������ͼ��
  appendChatBoxLayer(canvas_chatbox, title, *game, *screen);
  // ͨ��layer_chatboxָ����������ӷ���ز���screen�е�������ͼ��
  //*this->layer_chatbox = screen->getLayer(name_layer);
}

void AceAttorney::AceAttorneyChatbox::outputText(
    const AsciiTools::AsciiBasicString &text) {
  if (!isBind()) {
    gameLog->log("�ý�ɫ��δ��!", __LINE__, __FILE__);
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
    // �˴���Ҫ��layer_chatbox_text��layer_chatbox��layer_chatbox_name����ʾ״̬����Ϊfalse
    (*screen)[name_layer].setDisplayState(false);
    (*screen)["layer_chatbox_name"].setDisplayState(false);
    (*screen)["layer_chatbox"].setDisplayState(false);
  };
}

void AceAttorney::AceAttorneyChatbox::setTitle(const std::string &title) {
  // ����ͼ������߼�û��ʵ�֣��������Ҳ������´���
  if (screen->isExistLayer("layer_chatbox_name")) {
    const int chatbox_x = 0;
    const int chatbox_y = static_cast<int>(game->getWidth() * goldenRatio);

    Coord2d coord_chatbox(chatbox_x, chatbox_y);
    AsciiBasicString str_title = {title, false, clr_ChatBox_Name};

    setText(*screen, coord_chatbox, str_title, "layer_chatbox_name");
  } else {
    gameLog->log("������layer_chatbox_nameͼ�㣡", __LINE__, __FILE__);
  }
}