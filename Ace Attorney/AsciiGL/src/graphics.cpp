#include "graphics.h"

namespace AsciiGL {
AsciiBasicCanvas getCanvas(const AsciiBasicCanvas &canvas, Coord2d coordA,
                           Coord2d coordB) {
  if (!canvas.checkCoordinate(coordA) || !canvas.checkCoordinate(coordB) ||
      coordA == coordB) {
    throw AsciiBasicException(
        __FUNC__, "coordA或coordB的坐标非法!（①可能是因为其中或两个坐标非法 "
                  "②可能是因为两个坐标相等）");
  }

  const int length = abs(coordA.x - coordB.x) + 1;
  const int width = abs(coordA.y - coordB.y) + 1;
  const auto fill = canvas.getFill();

  AsciiBasicCanvas ret(length, width, fill);

  // 介于两点坐标为顶点的矩形，以矩形左上方的顶点为起点遍历坐标
  const Coord2d coord((coordA.x < coordB.x ? coordA.x : coordB.x),
                      (coordA.y < coordB.y ? coordA.y : coordB.y));

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      const auto str = canvas(coord.x + j, coord.y + i);
      ret.setCanvasData(Vec2d(j, i), str);
    }
  }
  return ret;
}

AsciiBasicCanvas overlapCanvas(const AsciiBasicCanvas &canvas,
                               const AsciiBasicCanvas &target, Coord2d coord) {
  AsciiBasicCanvas ret = target;
  auto coords = compareCanvas(target, canvas, coord);

  for (const auto &index : coords) {
    if (target.checkCoordinate(index)) {
      Coord2d coord_target = Vec2d(index);
      Coord2d coord_canvas = Vec2d(index.x - coord.x, index.y - coord.y);

      auto str_canvas = canvas.getCanvasData(coord_canvas);
      auto str_target = target.getCanvasData(coord_target);

      if (str_canvas == str_target) {
        continue;
      }

      AsciiBasicString str = str_canvas;

      for (int i = 0; i < str.size(); i++) {
        // 共有数据
        auto &index_chr_canvas = str[i];
        auto index_chr_target = str_target[i];
        //  对透明数据的处理
        bool trprState = index_chr_canvas.isTrpr();

        if (trprState) {
          index_chr_canvas = index_chr_target;
        }
        // 对RGBA数据的处理
        AsciiTextColor color = mixAsciiTextColor(index_chr_canvas.getColor(),
                                                 index_chr_target.getColor());
        index_chr_canvas.setColor(color);
      }

      ret.setCanvasData(coord_target, str);
    }
  }

  return ret;
}

void setText(AsciiBasicCanvas &canvas, Coord2d coord,
             const AsciiBasicString &str) {
  if (!canvas.checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }

  if (str.size() <= canvas.getBlockLength()) {
    canvas.setCanvasData(coord, str);
    return;
  }

  int strIndex = 0;
  int indexCount = 0;
  const int blockLength = canvas.getBlockLength();
  const int strSize = str.size();

  AsciiBasicString buffer;
  for (int i = 0; i + blockLength <= strSize; i += blockLength) {
    for (int j = 0; j < blockLength; j++) {
      buffer += str[i + j];
      strIndex = i + j;
    }
    canvas.setCanvasData(Vec2d(coord.x + indexCount, coord.y), buffer);
    indexCount++;
    buffer.clear();
  }
  if (strIndex != strSize - 1) {
    AsciiBasicString buffer;
    for (int i = strIndex + 1; i < strSize; i++) {
      buffer += str[i];
    }
    canvas.setCanvasData(Vec2d(coord.x + indexCount, coord.y), buffer);
  }
}

void setText(AsciiBasicLayer &layer, Coord2d coord,
             const AsciiBasicString &text) {
  const int length = getBlockNumber(text.size(), TRPRSTR.size());
  const int width = 1;
  const std::string name = layer.getName();

  AsciiBasicCanvas canvas(length, width);
  /* if (!canvas.checkCoordinate(coord)) {
    throw AsciiBasicException(__FUNC__, "coord非法!");
  }*/
  setText(canvas, Vec2d(0, 0), text);

  layer = AsciiBasicLayer(canvas, coord, name);
}

void setText(AsciiBasicLayerMngr &mngr, Coord2d coord,
             const AsciiBasicString &text, const std::string &layerName) {
  AsciiBasicLayer textLayer(layerName);
  setText(textLayer, coord, text);

  mngr[layerName] = textLayer;
}

void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str) {
  const int cLength = canvas.getLength();
  const int cWidth = canvas.getWidth();

  setLine(canvas, Vec2d(0, 0), Vec2d(cLength - 1, 0), str);
  setLine(canvas, Vec2d(0, cWidth - 1), Vec2d(cLength - 1, cWidth - 1), str);
  setLine(canvas, Vec2d(0, 0), Vec2d(0, cWidth - 1), str);
  setLine(canvas, Vec2d(cLength - 1, 0), Vec2d(cLength - 1, cWidth - 1), str);
}

std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas,
                                   Coord2d coord) {
  std::vector<Point2D> ret;
  for (int i = 0; i < canvas.getWidth(); i++) {
    for (int j = 0; j < canvas.getLength(); j++) {
      Coord2d coord_canvas = Vec2d(j, i);
      Coord2d coord_target = Vec2d(j + coord.x, i + coord.y);

      if (!target.checkCoordinate(coord_target)) {
        ret.emplace_back(coord_target);
        continue;
      }

      auto str_target = target.getCanvasData(coord_target);
      auto str_canvas = canvas.getCanvasData(coord_canvas);

      if (str_target != str_canvas) {
        ret.emplace_back(coord_target);
      }
    }
  }
  return ret;
}

void setLine(AsciiBasicCanvas &canvas, Coord2d coordA, Coord2d coordB,
             const AsciiBasicString &str, int level) {
  const int x1 = coordA.x;
  const int x2 = coordB.x;
  const int y1 = coordA.y;
  const int y2 = coordB.y;

  if (x1 == x2) {
    for (int y = y1; y <= y2; y++) {
      canvas.setCanvasData(Vec2d(x1, y), str);
    }
  } else if (y1 == y2) {
    for (int x = x1; x <= x2; x++) {
      canvas.setCanvasData(Vec2d(x, y1), str);
    }
  } else {
    const double targetX = abs(x2 - x1) + 1;
    const double deltaX = pow(10, -level);

    for (double i = 0; i < targetX; i += deltaX) {
      const Coord2d coord(
          static_cast<int>((coordA.x < coordB.x) ? x1 + i : x1 - i),
          static_cast<int>(y1 + getY(coordA, coordB, i)));

      canvas.setCanvasData(coord, str);
    }
  }
}

void reflect(AsciiBasicCanvas &canvas) {
  const int width = canvas.getWidth();
  const int indexWidth = (width / 2 - ((width == 0) ? 1 : 0));

  for (int i = 0; i < indexWidth; i++) {
    for (int j = 0; j < canvas.getLength(); j++) {
      const Coord2d reflectCoord = Vec2d(j, i);
      const Coord2d coord = Vec2d(j, canvas.getWidth() - i - 1);

      const auto reflectedStr = canvas.getCanvasData(reflectCoord);
      const auto str = canvas.getCanvasData(coord);

      canvas.setCanvasData(reflectCoord, str);
      canvas.setCanvasData(coord, reflectedStr);
    }
  }
}

#if defined(_WIN64) || defined(_WIN32)

void WinAPIDraw(const AsciiBasicCanvas &canvas, bool isClean) {
  static AsciiBasicCanvas canvasBuffer;
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

  if (isClean) {
    canvasBuffer.clear();
  }

  const auto coords = compareCanvas(canvasBuffer, canvas);

  for (const auto &coord : coords) {
    if (canvas.checkCoordinate(coord)) {
      SetConsoleCursorPosition(hndl, canvas.toConsoleCoord(coord));
      std::cout << canvas.getCanvasData(coord);
    }
  }
  canvasBuffer = canvas;
}

void WinAPIDraw(const AsciiBasicLayerMngr &mngr, bool isClear) {
  WinAPIDraw(mngr.getCanvas(), isClear);
}

void hideCursor() {
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CursorInfo;

  GetConsoleCursorInfo(hndl, &CursorInfo);
  CursorInfo.bVisible = false;

  SetConsoleCursorInfo(hndl, &CursorInfo);
}

#endif
} // namespace AsciiGL