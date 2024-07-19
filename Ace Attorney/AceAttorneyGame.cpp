#include "AceAttorneyGame.h"

namespace AceAttorney {
AceAttorneyGame::AceAttorneyGame(int length, int width) {
  this->length = length;
  this->width = width;

  screen = new AsciiBasicLayerMngr(length, width);
  audioEngine = createIrrKlangDevice();
  charas = new AceAttorneyCharaMngr();
  // threadPool = new ThreadPool(4);
  fps = 0;
  deltaTime = 0;
}

AceAttorneyGame::~AceAttorneyGame() {
  audioEngine->drop();

  delete screen;
  delete charas;
  // delete threadPool;
}

void AceAttorneyGame::addCharacter(AceAttorneyCharacter &chara) {
  chara.bind(this);
  charas->emplace_back(chara);
}

AsciiBasicLayerMngr *AceAttorneyGame::getScreen() { return screen; }

ISoundEngine *AceAttorneyGame::getISoundEngine() { return audioEngine; }

void AceAttorneyGame::executeCommands(
    const std::vector<std::string> &commands) {
  for (const auto &index : commands) {
    AnalyzeCommand anlyz(index);

    const auto cmd = anlyz.getCommand();
    const auto options = anlyz.getOptions();

    if (cmd == "text") {
      cmd_text(options);
    } else {
      gameLog->log("不存在这样的指令!");
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
  // std::thread thread_control([&]() { control(); });

  thread_update.join();
  thread_display.join();
  // thread_control.join();

  thread_callback.join();

  // threadPool->addTask(callback);
  // threadPool->addTask([&]() { display(); });
  // threadPool->addTask([&]() { control(); });
  // threadPool->addTask([&]() { update(); });
}

void AceAttorneyGame::update() {
  while (1) {
    std::string str_fps = "fps:" + std::to_string(fps);
    std::string str_deltaTime = "deltaTime:" + std::to_string(deltaTime) + "ms";
    {
      std::unique_lock<std::shared_mutex> lock(s_mtx);
      fps = getFPS(deltaTime);

      setText(*screen, Vec2d(0, 0), str_fps, "layer_fps");
      setText(*screen, Vec2d(0, 1), str_deltaTime, "layer_deltaTime");
    }
    /* for (int i = 0; i < screen->size(); i++) {
      std::string str_name = "layer_name" + std::to_string(i);

      std::unique_lock<std::shared_mutex> lock(s_mtx);
      setText(*screen, Vec2d(10, i), screen->getLayer(i).getName(), str_name);
    }*/
  }
}

void AceAttorneyGame::display() {
  while (1) {
    std::unique_lock<std::shared_mutex> lock(s_mtx);
    TimeMeasurer measurer(&deltaTime);

    WinAPIDraw(*screen);
  }
}

void AceAttorneyGame::control() {
  char input;
  while (1) {
    input = _getch();
    if (input == 'f') {
      {
        std::unique_lock<std::shared_mutex> lock(s_mtx);
        audioEngine->play2D("objection!.wav");
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
}

void AceAttorneyGame::cmd_text(const Option &options) {
  if (options.size() < 3) {
    gameLog->log("option太少!");
    exit(-1);
  }
  Coord2d coord(stringToInt(options[0]), stringToInt(options[1]));
  auto text = options[2];
  setText(*screen, coord, text);

  getchar();
}
} // namespace AceAttorney