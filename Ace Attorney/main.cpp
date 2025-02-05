#include "AceAttorneyGame.h"
#include "at_Debug.h"
#include <filesystem>

using namespace AceAttorney;

#if false

void convert(const std::string &path) {
  auto data = AsciiGL::getFileData(path);
  auto tokens_line = split(data, '\n');

  int length;
  int width;
  int blockLength;
  AsciiBasicString defaultFill;

  try {
    deserializeType(length, tokens_line[0]);
    deserializeType(width, tokens_line[1]);
    deserializeType(blockLength, tokens_line[2]);

    auto tokens_line_4 = split(tokens_line[3], ';');
    for (int i = 0; i < tokens_line_4.size(); i += 2) {
      char chr = (char)tokens_line_4[i][0];
      bool trprState = charToBool(tokens_line_4[i][1]);

      auto param_color = split(tokens_line_4[i + 1], ',');
      AsciiColor color(
          serializeType(param_color[0], param_color[1], param_color[2], 1.0));

      AsciiBasicChar chr_ascii(chr, {color, ASCII_COLOR_BLACK}, trprState);
      defaultFill += chr_ascii;
    }

    AsciiGL::AsciiBasicCanvas canvas(length, width, defaultFill);

    for (int i = 0; i < width; i++) {
      auto str_line = tokens_line[4 + i];

      std::string trprData_line;
      std::string color_line;

      bool has_color = (tokens_line.size() == 4 + width * 3);
      std::vector<std::string> tokens_color;
      if (has_color) {
        color_line = tokens_line[4 + width * 2 + i];
        tokens_color = split(color_line, ';');
      }

      bool has_trprData = (tokens_line.size() >= 4 + width * 2);
      if (has_trprData) {
        trprData_line = tokens_line[4 + width + i];
      }

      for (int j = 0; j < length; j++) {
        AsciiBasicString str;

        for (int k = 0; k < blockLength; k++) {
          const int index = j * blockLength + k;

          char chr = (char)str_line[index];
          bool trprState =
              (has_trprData) ? charToBool(trprData_line[index]) : false;

          AsciiTextColor color = {ASCII_COLOR_WHITE, ASCII_COLOR_BLACK};

          if (has_color) {
            auto param_color = split(tokens_color[index], ',');

            const int r = stringToInt(param_color[0]);
            const int g = stringToInt(param_color[1]);
            const int b = stringToInt(param_color[2]);

            AsciiColor basic_color(r, g, b);

            const AsciiTextColor text_color = {basic_color, ASCII_COLOR_BLACK};

            color = text_color;
          }

          AsciiBasicChar chr_ascii(chr, color, trprState);

          str += chr_ascii;
        }

        canvas[Vec2d(j, i)] = str;
      }
    }

    std::filesystem::path file_path(path);
    const std::string name = "new_out/" + file_path.stem().string() + ".asc2";
    canvas.save(name);
  } catch (...) {
    throw AsciiBasicException(__FUNC__, "转换失败!");
  }
}

void batchConvert(const std::string &file_path) {
  const std::filesystem::path path(file_path);

  for (const auto &index : std::filesystem::directory_iterator(path)) {
    if (index.path().extension().string() == ".dat") {
      std::cout << index.path().string() << std::endl;

      try {
        convert(index.path().string());
      } catch (...) {
        std::cout << "转换失败!" << std::endl;
        continue;
      }
    }
  }
}

void batchshow(const std::string &file_path) {
  const std::filesystem::path path(file_path);

  for (const auto &index : std::filesystem::directory_iterator(path)) {
    if (index.path().extension().string() == ".asc2") {
      std::cout << index.path().string() << std::endl;

      AsciiGL::AsciiBasicCanvas canvas(index.path().string());
      canvas.info();

      std::cout << std::endl;
      std::cout << "=====================================" << std::endl;
    }
  }
}

#endif

AsciiGL::AsciiBasicCanvas conv(const std::string &path) {
  HANDLE hFile = CreateFileA(path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE) {
    throw AsciiTools::AsciiBasicException(__FUNC__, "无法打开文件");
  }

  // 读取位图文件头
  BITMAPFILEHEADER fileHeader;
  ReadFile(hFile, &fileHeader, sizeof(fileHeader), NULL, NULL);

  // 读取位图信息头
  BITMAPINFOHEADER infoHeader;
  ReadFile(hFile, &infoHeader, sizeof(infoHeader), NULL, NULL);

  // 获取图像宽度和高度
  int width = infoHeader.biWidth;
  int height = infoHeader.biHeight;

  // 定位到像素数据
  SetFilePointer(hFile, fileHeader.bfOffBits, NULL, FILE_BEGIN);

  AsciiGL::AsciiBasicCanvas canvas(width, height);

  // 遍历每一行
  for (int y = height - 1; y >= 0; --y) {
    // 遍历每一列
    for (int x = 0; x < width; ++x) {
      BYTE rgb[3];
      // 读取像素的 RGB 值
      ReadFile(hFile, rgb, 3, NULL, NULL);
      const int r = static_cast<int>(rgb[2]);
      const int g = static_cast<int>(rgb[1]);
      const int b = static_cast<int>(rgb[0]);
      canvas.setCanvasData(Vec2d(x, y), {"  ", false, {{0, 0, 0}, {r, g, b}}});
    }
  }

  // 关闭文件句柄
  CloseHandle(hFile);

  return canvas;
}

int main() {
  try {
    AceAttorneyCharacter chara_1("0x2ed_(AsciiGLの创世主)", 21);
    AceAttorneyCharacter chara_2("成步堂龙一", 21);
    AceAttorneyCharacter chara_3("审判长", 21);
    AceAttorneyCharacter sys("旁白", 21);
    // AceAttorneyGame game(23, 15);
    AceAttorneyGame game(40, 25);

    game.addCharacter(chara_1);
    game.addCharacter(chara_2);
    game.addCharacter(chara_3);
    game.addCharacter(sys);
    game.run([&]() {
      game.getISoundEngine()->play2D("bgm2.ogg", true);

      while (true) {
        chara_1.objection();
        chara_1.chatBox("哈哈哈哈哈，没想到吧，我终于还是重置了逆转裁判！");
        chara_1.chatBox("虽然说优化不怎么样，帧率不稳定，逐字显示不流畅，但是我"
                        "真的重置了！",
                        100);
        chara_2.chatBox("？？？你是......谁......？？？");
        chara_2.chatBox("你怎么出现在法庭上？？？");
        chara_1.objection();
        chara_1.chatBox("那是因为我就是这个程序の主宰!!!", 10);
        chara_1.chatBox(
            "哈哈哈哈哈哈哈......哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈！！！！", 5);
        chara_1.chatBox("哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈"
                        "哈哈哈！！！！",
                        1);
        chara_3.chatBox("来人啊！把这位突然闯入的听证者踢出法庭！！！", 10);
        chara_1.chatBox("不......不要啊！！！我要见证这个程序的成功运行！！！",
                        10);
        sys.chatBox("0x2ed_被法警以强制的手段拖出了法庭......", 20);

        chara_2.chatBox("呼......真奇怪的听证者呢......");
      }
    });
  } catch (const AsciiBasicException &e) {
    std::cout << e.what() << std::endl;
  }

  /* initAsciiGL();
  initWindowRGB();
  initWindow(40, 25);

  auto canvas = conv("test.bmp");
  getchar();
  canvas.show();
  getchar();
  canvas.save("法庭背景.asc2");

  getchar();*/

  /* std::locale lc_zh("zh_CN");
  std::wcout.imbue(lc_zh);
  std::wstring str = L"你好helloみさか みこと";
  for (int i = 0; i < str.size(); i++) {
    std::wcout << i << "\t" << str[i] << std::endl;
  }*/
  /* const int count = 999999;
  {
    EfficiencyDebug ef;
    std::string str;
    for (int i = 0; i < count; i++) {
      str += "HelloWorld";
    }
  }
  {
    EfficiencyDebug ef;
    AsciiBasicString str;
    for (int i = 0; i < count; i++) {
      str += "HelloWorld";
    }
  }

  AsciiGL::AsciiBasicLayerMngr mngr;
  {
    while (1) {
      EfficiencyDebug ef;
      for (int i = 0; i < count; i++) {
        AsciiGL::setText(mngr[i], Vec2d(0, 0), "Hello world!");
      }
    }
  }*/

  return 0;
}