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
  this->coord = layer.coord;
  this->name = layer.name;
  this->centerCoord = layer.centerCoord;
  this->displayState = layer.displayState;
}

AsciiBasicLayer::AsciiBasicLayer(AsciiBasicLayer &&layer) noexcept
    : AsciiBasicCanvas(std::move(layer)) {
  this->coord = layer.coord;
  this->name = layer.name;
  this->centerCoord = layer.centerCoord;
  this->displayState = layer.displayState;
}

void AsciiBasicLayer::setCenterCoordinate(Coord2d coord) {
  this->centerCoord = coord;
}

bool AsciiBasicLayer::operator==(const AsciiBasicLayer &layer) const {
  return (AsciiBasicCanvas::operator==(layer) && this->coord == layer.coord &&
          this->name == layer.name && this->centerCoord == layer.centerCoord &&
          this->displayState == layer.displayState)
             ? true
             : false;
}

bool AsciiBasicLayer::operator==(AsciiBasicLayer &&layer) const noexcept {
  bool ret =
      (AsciiBasicCanvas::operator==(layer) && this->coord == layer.coord &&
       this->name == layer.name && this->centerCoord == layer.centerCoord &&
       this->displayState == layer.displayState)
          ? true
          : false;
  layer.datas = nullptr;

  return ret;
}

bool AsciiBasicLayer::operator!=(const AsciiBasicLayer &layer) const {
  return !(*this == layer);
}

bool AsciiBasicLayer::operator!=(AsciiBasicLayer &&layer) const noexcept {
  return !(*this == std::move(layer));
}

AsciiBasicLayer &AsciiBasicLayer::operator=(const AsciiBasicLayer &layer) {
  AsciiBasicCanvas::operator=(layer);
  this->coord = layer.coord;
  this->name = layer.name;
  this->displayState = layer.displayState;
  this->centerCoord = layer.centerCoord;

  return *this;
}

AsciiBasicLayer &AsciiBasicLayer::operator=(AsciiBasicLayer &&layer) noexcept {
  AsciiBasicCanvas::operator=(std::move(layer));
  this->coord = layer.coord;
  this->name = layer.name;
  this->displayState = layer.displayState;
  this->centerCoord = layer.centerCoord;

  return *this;
}
} // namespace AsciiGL