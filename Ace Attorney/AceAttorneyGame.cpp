#include "AceAttorneyGame.h"

namespace AceAttorney {
AceAttorneyGame::AceAttorneyGame() {
  length = 0;
  width = 0;

  screen = std::make_shared<AsciiGL::AsciiBasicLayerMngr>();
  audioEngine = irrklang::createIrrKlangDevice();
  audioEngine->setSoundVolume(0.5);
  charas = std::make_shared<AceAttorneyCharaMngr>();
  s_mtx = std::make_shared<std::shared_mutex>();
  chatbox = std::make_shared<AceAttorneyChatbox>();
  chatbox->bind(this);
  // 暂不考虑初始化ChatBox，即不调用initChatBox()函数。
  // 因为调用该函数会在screen中创建图层，会导致资源浪费。
  // 而且AceAttorneyGame()是默认构造函数，一般不会进行详细的对象具象化，
  // 仅仅是保证AceAttorneyGame对象的各数据成员的值是默认的

  // this->chatbox->initChatBox(10, "ChatBox");

  fps = 0;
  deltaTime = 0;
}
// 可考虑一下把上下两个构造函数优化一下，不要写得如此冗杂重复
AceAttorneyGame::AceAttorneyGame(int length, int width) {
  this->length = length;
  this->width = width;

  screen = std::make_shared<AsciiGL::AsciiBasicLayerMngr>(length, width);
  audioEngine = irrklang::createIrrKlangDevice();
  audioEngine->setSoundVolume(0.5);
  charas = std::make_shared<AceAttorneyCharaMngr>();
  s_mtx = std::make_shared<std::shared_mutex>();
  chatbox = std::make_shared<AceAttorneyChatbox>();
  chatbox->bind(this);

  fps = 0;
  deltaTime = 0;
  // 此处screen的背景图层添加和chatbox的初始化顺序不能调换！
  // 因为一旦顺序颠倒，会导致chatbox的图像会被作为背景图层，
  // 而screen即将添加的真正的背景图层会被当做普通图层，违反常识

  // screen->appendLayer(
  //    {AsciiGL::AsciiBasicLayer({length, width, str_Background}, Vec2d(0,
  //    0))});

  screen->appendLayer(
      {AsciiGL::AsciiBasicCanvas("法庭背景.asc2"), Vec2d(0, 0)});

  // game中唯一的chatbox对象，该对象负责处理所有角色的对话
  this->chatbox->initChatBox(10, "ChatBox");
}

AceAttorneyGame::AceAttorneyGame(const AceAttorneyGame &game) {
  this->screen = std::make_shared<AsciiGL::AsciiBasicLayerMngr>(*game.screen);
  this->audioEngine = irrklang::createIrrKlangDevice();
  this->charas = std::make_shared<AceAttorneyCharaMngr>(*game.charas);
  this->length = game.length;
  this->width = game.width;
  this->deltaTime = 0;
  this->fps = 0;
  this->s_mtx = std::make_shared<std::shared_mutex>();
  this->chatbox = game.chatbox;
}

AceAttorneyGame::~AceAttorneyGame() { audioEngine->drop(); }

void AceAttorneyGame::addCharacter(AceAttorneyCharacter &chara) {
  chara.bind(this);
  // charas->emplace_back(chara);
}

AceAttorneyGame::pScreen AceAttorneyGame::getScreen() { return screen; }

irrklang::ISoundEngine *AceAttorneyGame::getISoundEngine() {
  return audioEngine;
}

void AceAttorneyGame::executeCommands(
    const std::vector<std::string> &commands) {
  for (const auto &index : commands) {
    AnalyzeCommand anlyz(index);

    const auto cmd = anlyz.getCommand();
    const auto options = anlyz.getOptions();

    if (cmd == "text") {
      cmd_text(options);
    } else {
      gameLog->log("不存在这样的指令!", __LINE__, __FILE__);
    }
  }
}

void AceAttorneyGame::executeCommands(const std::string &path) {
  auto fileData = readFile(path);
  auto tokens = split(fileData, '\n');

  executeCommands(tokens);
}

void AceAttorneyGame::run(const std::string &path) {
  initWindowRGB();
  initWindow(length, width);
  initAsciiGL();
  std::thread thread_execCmd([&]() { executeCommands(path); });
  std::thread thread_display([&]() { display(); });
  std::thread thread_control([&]() { control(); });
  std::thread thread_update([&]() { update(); });

  thread_execCmd.join();
  thread_display.join();
  thread_control.join();
  thread_update.join();
}

void AceAttorneyGame::run(const std::function<void()> &callback) {
  initWindowRGB();
  initWindow(length, width);
  initAsciiGL();
  std::thread thread_update([&]() { update(); });
  std::thread thread_display([&]() { display(); });
  std::thread thread_callback(callback);
  //   std::thread thread_control([&]() { control(); });

  thread_update.join();
  thread_display.join();
  //  thread_control.join();

  thread_callback.join();
}

void AceAttorneyGame::update() {
  while (1) {
    std::string str_fps = "fps:" + std::to_string(fps);
    std::string str_deltaTime = "△time:" + std::to_string(deltaTime);

    fps = getFPS(deltaTime);

    std::shared_lock<std::shared_mutex> lock(*s_mtx);
    WinAPIText({0, 0}, str_fps);
    WinAPIText({0, 1}, str_deltaTime);
    // WinAPIText({0, 1}, "Ace-Attorney powered by AsciiGL");
    // WinAPIText({0, 2}, "Author: 0x2ed_");
  }
}

void AceAttorneyGame::display() {
  while (1) {
    TimeMeasurer measurer(&deltaTime);
    std::unique_lock<std::shared_mutex> lock(*s_mtx);

    WinAPIDraw(*screen);
  }
}

void AceAttorneyGame::control() {
  char input;
  while (1) {
    input = _getch();
    if (input == 'f') {
      {
        std::unique_lock<std::shared_mutex> lock(*s_mtx);
        audioEngine->play2D("objection!.wav");
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
}

void AceAttorneyGame::cmd_text(const Option &options) {
  if (options.size() < 3) {
    gameLog->log("option太少!", __LINE__, __FILE__);
    exit(-1);
  }
  Coord2d coord(stringToInt(options[0]), stringToInt(options[1]));
  auto text = options[2];
  setText(*screen, coord, text);

  getchar();
}

AsciiGL::AsciiBasicCanvas AceAttorney::getChatBoxCanvas(AceAttorneyGame &game) {
  int chatBoxLength = 0;
  int chatBoxWidth = 0;
  {
    std::shared_lock<std::shared_mutex> lock(*game.getSharedMutex());
    chatBoxLength = game.getLength();
    chatBoxWidth = static_cast<int>(game.getWidth() * (1.0 - goldenRatio));
  }

  AsciiGL::AsciiBasicCanvas canvas_chatbox(chatBoxLength, chatBoxWidth,
                                           str_ChatBox);
  setLine(canvas_chatbox, Vec2d(0, 0), Vec2d(chatBoxLength - 1, 0), TRPRSTR);

  return canvas_chatbox;
}

void appendChatBoxLayer(const AsciiGL::AsciiBasicCanvas &canvas,
                        const std::string &name, AceAttorneyGame &game,
                        AsciiGL::AsciiBasicLayerMngr &mngr) {
  AsciiBasicString str_name = {name, false, clr_ChatBox_Name};

  std::shared_ptr<std::shared_mutex> s_mtx = nullptr;
  {
    std::shared_lock<std::shared_mutex> lock(*game.getSharedMutex());
    s_mtx = game.getSharedMutex();
  }
  const int chatbox_x = 0;
  int chatbox_y = 0;
  {
    std::shared_lock<std::shared_mutex> lock(*s_mtx);
    chatbox_y = static_cast<int>(game.getWidth() * goldenRatio);
  }

  Coord2d coord_chatbox(chatbox_x, chatbox_y);
  AsciiGL::AsciiBasicLayer layer_chatbox(canvas, coord_chatbox,
                                         "layer_chatbox");

  bool isExist = false;
  {
    std::shared_lock<std::shared_mutex> lock(*s_mtx);
    isExist = mngr.isExistLayer("layer_chatbox");
  }

  if (!isExist) {
    std::unique_lock<std::shared_mutex> lock(*s_mtx);
    mngr.appendLayer(layer_chatbox);
  } else {
    std::unique_lock<std::shared_mutex> lock(*s_mtx);
    mngr.setLayer(layer_chatbox, "layer_chatbox");
  }
  std::unique_lock<std::shared_mutex> lock(*s_mtx);
  setText(mngr, coord_chatbox, str_name, "layer_chatbox_name");
}
} // namespace AceAttorney