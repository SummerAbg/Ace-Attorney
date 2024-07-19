#include "agl_BasicCanvas.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicCanvas::AsciiBasicCanvas(int length, int width,
                                   const AsciiBasicString &str) {
  this->length = length;
  this->width = width;
  defaultFill = str;
  blockLength = defaultFill.size();
  datas = CanvasData(length, width, str);
}

AsciiBasicCanvas::AsciiBasicCanvas(const std::string &path) { load(path); }

AsciiBasicCanvas::AsciiBasicCanvas(const AsciiBasicCanvas &canvas) {
  this->length = canvas.getLength();
  this->width = canvas.getWidth();
  this->defaultFill = canvas.getFill();
  this->blockLength = canvas.getBlockLength();
  this->datas = canvas.getCanvasData();
}

void AsciiBasicCanvas::info() const {
  std::cout << "Length:" << length << std::endl
            << "Width:" << width << std::endl
            << "DefaultFill:" << defaultFill << std::endl
            << "BlockLength:" << blockLength << std::endl
            << "Size:" << datas.size() << std::endl;
}

std::string AsciiBasicCanvas::toString() const {
  std::string ret;

  AsciiBasicString buffer = this->getAsciiBasicString();
  ret = buffer.toString();

  return ret;
}

AsciiBasicString &AsciiBasicCanvas::operator[](const Coord2d &coord) {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return datas[coord];
}

const AsciiBasicString &
AsciiBasicCanvas::operator[](const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return datas[coord];
}

const AsciiBasicString &AsciiBasicCanvas::operator()(int x, int y) const {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return datas(x, y);
}

void AsciiBasicCanvas::setCanvasData(const Coord2d &coord,
                                     const AsciiBasicString &fill) {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }

  if (fill.size() >= blockLength) {
    datas[coord] = cutString(fill, blockLength - 1);
    return;
  }

  if (fill.size() < blockLength) {
    datas[coord] = overlapString(datas[coord], fill, 0, true);
  }
}

AsciiBasicString AsciiBasicCanvas::getCanvasData(const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return datas[coord];
}

AsciiBasicString AsciiBasicCanvas::getAsciiBasicString() const {
  AsciiBasicString ret;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      ret += datas(j, i);
    }
    if (i < width - 1)
      ret += "\n";
  }
  return ret;
}

void AsciiBasicCanvas::clear(bool flag) {
  if (flag) {
    *this = AsciiBasicCanvas();
  } else {
    this->datas = CanvasData(length, width, defaultFill);
  }
}

void AsciiBasicCanvas::save(const std::string &path) const {
  std::ofstream outFile(path.c_str());

  if (!outFile.is_open()) {
    throw AsciiBasicException(__FUNC__, FileNotExist);
  }

  outFile << serialize(this);

  outFile.close();
}

void AsciiBasicCanvas::load(const std::string &path) {
  auto tokens = split(path, '.');
  if (tokens.size() <= 1) {
    throw AsciiBasicException(__FUNC__, "路径名非法!");
  } else if (tokens[1] != "asc2") {
    throw AsciiBasicException(__FUNC__, "该文件并非asc2文件!");
  }

  *this = AsciiBasicCanvas();

  std::string fileData = getFileData(path);
  deserialize(this, fileData);
}

void AsciiBasicCanvas::show() const {
  std::cout << this->getAsciiBasicString();
}

bool AsciiBasicCanvas::checkCoordinate(const Coord2d &coord) const {
  return datas.checkCoordinate(coord);
}

COORD AsciiBasicCanvas::toConsoleCoord(const Coord2d &coord) const {
  COORD ret;
  ret.X = static_cast<short>(coord.x * blockLength);
  ret.Y = static_cast<short>(coord.y);
  return ret;
}

bool AsciiBasicCanvas::operator==(const AsciiBasicCanvas &canvas) const {
  return (this->datas == canvas.getCanvasData() &&
          this->blockLength == canvas.getBlockLength() &&
          this->getFill() == canvas.getFill())
             ? true
             : false;
}

bool AsciiBasicCanvas::operator!=(const AsciiBasicCanvas &canvas) const {
  return !(*this == canvas);
}

std::string AsciiBasicCanvas::getSerializeStr() const {
  std::string ret;
  ret += spliceString("\n", length, width, blockLength);
  ret += "\n";
  ret += serialize(&defaultFill) + "\n";

  ret += this->toString() + "\n";

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      const auto trprData = datas[Vec2d(j, i)].getTrprData();

      for (const auto &index : trprData) {
        ret += std::to_string(index);
      }
    }
    ret += "\n";
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      const auto colorData = datas[Vec2d(j, i)].getTextColorData();

      for (const auto &index : colorData) {
        ret += index.toString();
      }
    }
    ret += "\n";
  }
  return ret;
}

void AsciiBasicCanvas::loadSerializeStr(const std::string &str) {
  const auto tokens_row = split(str, '\n');

  if (tokens_row.size() < 4) {
    throw AsciiBasicException(__FUNC__, FileFormatError);
  }

  this->length = stringToInt(tokens_row[0]);
  this->width = stringToInt(tokens_row[1]);
  this->blockLength = stringToInt(tokens_row[2]);
  datas.setLength(length);
  datas.setWidth(width);

  deserialize(&defaultFill, tokens_row[3]);

  // 是否有完整颜色数据
  bool clr_flag = (tokens_row.size() == 4 + width * 3);

  // 颜色块
  std::vector<std::string> colorBlocks;

  for (int fileLine = 4; fileLine < width + 4; fileLine++) {
    if (clr_flag) {
      colorBlocks = split(tokens_row[fileLine + width * 2], ';');
    }

    for (int i = 0; i < length; i++) {
      std::string text;
      AsciiTrprData trprData;
      AsciiTextColorData color;

      for (int j = 0; j < blockLength; j++) {
        const int index = i * blockLength + j;

        text += tokens_row[fileLine][index];
        ////////////////////////////////////////////////text
        bool isTrpr = (tokens_row.size() >= 4 + width * 2)
                          ? charToBool(tokens_row[fileLine + width][index])
                          : false;
        trprData.emplace_back(isTrpr);
        ////////////////////////////////////////////////trprData

        AsciiTextColor clr = AsciiTextColor(colorBlocks[index]);

        color.emplace_back(clr);
        ////////////////////////////////////////////////color
      }
      AsciiBasicString data = {text, color, trprData};
      datas.append(data);
    }
  }
}
} // namespace AsciiGL