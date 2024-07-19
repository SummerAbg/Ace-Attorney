#include "AceAttorneyGame.h"
#include "at_Debug.h"

using namespace AceAttorney;

int main() {
  try {
    AceAttorneyCharacter chara_1("成步堂龙一", 21);
    AceAttorneyCharacter chara_2("御剑怜侍", 24);
    AceAttorneyGame game(23, 15);

    game.addCharacter(chara_1);
    game.addCharacter(chara_2);
    game.run([&]() {
      while (1) {
        chara_1.chatBox("你好，你是御剑怜侍吗？", 10);
        chara_2.chatBox("是的......怎么?", 10);
      }
    });
  } catch (const AsciiBasicException &e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "其他异常!" << std::endl;
  }
  /* std::locale lc_zh("zh_CN");
  std::wcout.imbue(lc_zh);
  std::wstring str = L"你好helloみさか みこと";
  for (int i = 0; i < str.size(); i++) {
    std::wcout << i << "\t" << str[i] << std::endl;
  }*/
  /* const int count = 999;
  {
    EfficiencyDebug ef;
    std::string str;
    for (int i = 0; i < count; i++)
      str += "Hello";
  }
  {
    EfficiencyDebug ef;
    AsciiBasicString str;
    for (int i = 0; i < count; i++)
      str += "Hello";
  }*/
  /* AsciiBasicLayerMngr mngr;
  {
    while (1) {
      EfficiencyDebug ef;
      for (int i = 0; i < 6666; i++) {
        setText(mngr, Vec2d(0, 0), "Hello world!", "A");
      }
    }
  }*/
  /* try {
    AsciiBasicCanvas canvas("canvas.asc2");
    canvas.show();

    std::cout << std::endl;

    auto newCanvas = getCanvas(canvas, Vec2d(0, 0), Vec2d(5, 5));
    newCanvas.show();
  } catch (const AsciiBasicException &e) {
    std::cout << e.what() << std::endl;
  }*/
  return 0;
}