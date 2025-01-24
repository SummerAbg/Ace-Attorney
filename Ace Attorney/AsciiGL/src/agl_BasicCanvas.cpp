#include "agl_BasicCanvas.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicCanvas::AsciiBasicCanvas() {
  blockLength = 0;
  datas = std::make_shared<CanvasData>();
}

AsciiBasicCanvas::AsciiBasicCanvas(int length, int width,
                                   const AsciiBasicString &str) {
  blockLength = str.size();
  datas = std::make_shared<CanvasData>(length, width, str);
}

AsciiBasicCanvas::AsciiBasicCanvas(const std::string &path) { load(path); }

AsciiBasicCanvas::AsciiBasicCanvas(const AsciiBasicCanvas &canvas) {
  this->blockLength = canvas.blockLength;
  this->datas = std::make_shared<CanvasData>(*canvas.datas);
}

AsciiBasicCanvas::AsciiBasicCanvas(AsciiBasicCanvas &&canvas) noexcept {
  this->blockLength = canvas.blockLength;
  this->datas = canvas.datas;
  canvas.datas = nullptr;
}

void AsciiBasicCanvas::info() const {
  std::cout << "AsciiBasicCanvas对象" << std::endl;
  std::cout << "length:" << datas->getLength() << std::endl
            << "width:" << datas->getWidth() << std::endl
            << "blockLength:" << blockLength << std::endl
            << "background_element:" << datas->getBackgroundElement()
            << std::endl
            << "size:" << datas->size() << std::endl;
  show();
}

std::string AsciiBasicCanvas::toString() const {
  return this->getAsciiBasicString().toString();
}

AsciiBasicString &AsciiBasicCanvas::operator[](const Coord2d &coord) {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*datas)[coord];
}

const AsciiBasicString &
AsciiBasicCanvas::operator[](const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*datas)[coord];
}

const AsciiBasicString &AsciiBasicCanvas::operator()(int x, int y) const {
  if (!checkCoordinate(Vec2d(x, y))) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return (*datas)(x, y);
}

void AsciiBasicCanvas::setCanvasData(const Coord2d &coord,
                                     const AsciiBasicString &fill) {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }

  if (fill == datas->getElement(coord)) {
    return;
  }

  if (fill.size() >= blockLength) {
    (*datas)[coord] = cutString(fill, blockLength - 1);
    return;
  }

  if (fill.size() < blockLength) {
    (*datas)[coord] = overlapString((*datas)[coord], fill, 0, true);
  }
}

AsciiBasicString AsciiBasicCanvas::getCanvasData(const Coord2d &coord) const {
  if (!checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }
  return this->datas->getElement(coord);
}

AsciiBasicString AsciiBasicCanvas::getAsciiBasicString() const {
  AsciiBasicString ret;
  for (int i = 0; i < datas->getWidth(); i++) {
    for (int j = 0; j < datas->getLength(); j++) {
      AsciiBasicString buffer;

      bool isElement = datas->isElementCoord(Vec2d(j, i));
      if (isElement) {
        buffer = datas->getElement(j, i);
      } else {
        buffer = datas->getBackgroundElement();
      }
      ret += buffer;
    }
    ret += "\n";
  }
  return ret;
}

void AsciiBasicCanvas::clear(bool flag) {
  if (flag) {
    *this = AsciiBasicCanvas();
  } else {
    this->datas = std::make_shared<CanvasData>();
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
  return datas->checkCoordinate(coord);
}

COORD AsciiBasicCanvas::toConsoleCoord(const Coord2d &coord) const {
  COORD ret;
  ret.X = static_cast<short>(coord.x * blockLength);
  ret.Y = static_cast<short>(coord.y);
  return ret;
}

bool AsciiBasicCanvas::operator==(const AsciiBasicCanvas &canvas) const {
  return (*this->datas == *canvas.datas &&
          this->blockLength == canvas.blockLength)
             ? true
             : false;
}

bool AsciiBasicCanvas::operator==(AsciiBasicCanvas &&canvas) const noexcept {
  bool ret =
      (*this->datas == *canvas.datas && this->blockLength == canvas.blockLength)
          ? true
          : false;

  canvas.datas = nullptr;

  return ret;
}

bool AsciiBasicCanvas::operator!=(const AsciiBasicCanvas &canvas) const {
  return !(*this == canvas);
}

bool AsciiBasicCanvas::operator!=(AsciiBasicCanvas &&canvas) const noexcept {
  return !(*this == std::move(canvas));
}

AsciiBasicCanvas &AsciiBasicCanvas::operator=(const AsciiBasicCanvas &canvas) {
  this->blockLength = canvas.blockLength;
  *this->datas = *canvas.datas;
  // printf("Canvas拷贝%d\t%d\n", this->datas->size(), canvas.datas->size());
  // getchar();

  return *this;
}

AsciiBasicCanvas &
AsciiBasicCanvas::operator=(AsciiBasicCanvas &&canvas) noexcept {
  this->blockLength = canvas.blockLength;
  this->datas = canvas.datas;
  canvas.datas = nullptr;

  return *this;
}

std::string AsciiBasicCanvas::getSerializeStr() const {
  return serializeType(blockLength, *datas);
}

void AsciiBasicCanvas::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  if (tokens.size() < 2) {
    throw AsciiBasicException(__FUNC__, FileFormatError);
  }

  deserializeType(blockLength, tokens[0]);
  deserializeType(*datas, tokens[1]);
}
} // namespace AsciiGL