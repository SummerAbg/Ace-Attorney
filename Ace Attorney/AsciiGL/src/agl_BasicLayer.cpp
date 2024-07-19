#include "agl_BasicLayer.h"

namespace AsciiGL {
AsciiBasicLayer::AsciiBasicLayer() : AsciiBasicCanvas() {
  name = makeName("untitledLayer");
  displayState = true;
  centerCoord = Vec2d(0, 0);
  coord = Vec2d(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coord2d coord)
    : AsciiBasicCanvas(canvas) {
  this->coord = coord;

  name = makeName("untitledLayer");
  displayState = true;
  centerCoord = Vec2d(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coord2d coord,
                                 const std::string &name, bool displayState)
    : AsciiBasicCanvas(canvas) {
  this->coord = coord;
  this->name = name;
  this->displayState = displayState;
  centerCoord = Vec2d(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const std::string &name) : AsciiBasicCanvas() {
  this->name = name;
  coord = Vec2d(0, 0);
  displayState = true;
  centerCoord = Vec2d(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicLayer &layer)
    : AsciiBasicCanvas(layer) {
  this->coord = layer.getCoordinate();
  this->name = layer.getName();
  this->centerCoord = layer.getCenterCoordinate();
  this->displayState = layer.isDisplay();
}

void AsciiBasicLayer::setCenterCoordinate(Coord2d coord) {
  this->centerCoord = coord;
}

bool AsciiBasicLayer::operator==(const AsciiBasicLayer &layer) const {
  return ((AsciiBasicCanvas)(*this) == (AsciiBasicCanvas)layer &&
          this->coord == layer.getCoordinate() && this->name == layer.getName())
             ? true
             : false;
}

bool AsciiBasicLayer::operator!=(const AsciiBasicLayer &layer) const {
  return !(*this == layer);
}
} // namespace AsciiGL