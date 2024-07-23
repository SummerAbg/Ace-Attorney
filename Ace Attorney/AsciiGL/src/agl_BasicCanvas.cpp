#include "agl_BasicCanvas.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicCanvas::AsciiBasicCanvas(int length, int width,
                                   const AsciiBasicString &str) {
  defaultFill = str;
  blockLength = defaultFill.size();
  datas = CanvasData(length, width, str);
}

AsciiBasicCanvas::AsciiBasicCanvas(const std::string &path) { load(path); }

AsciiBasicCanvas::AsciiBasicCanvas(const AsciiBasicCanvas &canvas) {
  this->defaultFill = canvas.getFill();
  this->blockLength = canvas.getBlockLength();
  this->datas = canvas.getCanvasData();
}

void AsciiBasicCanvas::info() const {
  std::cout << "Length:" << datas.getLength() << std::endl
            << "Width:" << datas.getWidth() << std::endl
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

  for (int i = 0; i < datas.getWidth(); i++) {
    for (int j = 0; j < datas.getLength(); j++) {
      ret += datas(j, i);
    }
    if (i < datas.getWidth() - 1)
      ret += "\n";
  }
  return ret;
}

void AsciiBasicCanvas::clear(bool flag) {
  if (flag) {
    *this = AsciiBasicCanvas();
  } else {
    this->datas = CanvasData(datas.getLength(), datas.getWidth(), defaultFill);
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
  std::filesystem::path file_path(path);
  if (file_path.extension().string() != ".asc2") {
    throw AsciiBasicException(__FUNC__, "该文件并非asc2文件!");
  }

  *this = AsciiBasicCanvas();

  std::string fileData = getFileData(path);
  deserializeType(*this, fileData);
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
  std::string ret = serializeType(blockLength, defaultFill, datas);
  return ret;
}

void AsciiBasicCanvas::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() < 3) {
    throw AsciiBasicException(__FUNC__, FileFormatError);
  }

  deserializeType(blockLength, tokens[0]);
  deserializeType(defaultFill, tokens[1]);
  deserializeType(datas, tokens[2]);
}
} // namespace AsciiGL