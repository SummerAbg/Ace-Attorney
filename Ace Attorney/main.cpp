#include "AceAttorneyGame.h"
#include "at_Debug.h"
#include <filesystem>

using namespace AceAttorney;

void convert(const std::string &path) {
  auto data = getFileData(path);
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

    AsciiBasicCanvas canvas(length, width, defaultFill);

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
    throw AsciiBasicException(__FUNC__, "×ª»»Ê§°Ü!");
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
        std::cout << "×ª»»Ê§°Ü!" << std::endl;
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

      AsciiBasicCanvas canvas(index.path().string());
      canvas.info();
      canvas.show();

      std::cout << std::endl;
      std::cout << "=====================================" << std::endl;
    }
  }
}

int main() {
  try {
    AceAttorneyCharacter chara_1("³É²½ÌÃÁúÒ»", 21);
    AceAttorneyCharacter chara_2("Óù½£Á¯ÊÌ", 24);
    AceAttorneyGame game(23, 15);

    game.addCharacter(chara_1);
    game.addCharacter(chara_2);
    game.run([&]() {
      while (1) {
        chara_1.chatBox("ÄãºÃ£¬ÄãÊÇÓù½£Á¯ÊÌÂð£¿", 10);
        chara_2.chatBox("ÊÇµÄ......ÔõÃ´?", 10);
        chara_1.objection();
      }
    });
  } catch (const AsciiBasicException &e) {
    std::cout << e.what() << std::endl;
  }
  /* std::locale lc_zh("zh_CN");
  std::wcout.imbue(lc_zh);
  std::wstring str = L"ÄãºÃhello¤ß¤µ¤« ¤ß¤³¤È";
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
  return 0;
}