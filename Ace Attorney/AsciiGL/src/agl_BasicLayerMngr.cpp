#include "agl_BasicLayerMngr.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicLayerMngr::AsciiBasicLayerMngr(int length, int width,
                                         const AsciiBasicString &str) {
  AsciiBasicCanvas canvas(length, width, str);
  AsciiBasicLayer layer = {canvas, Vec2d(0, 0), "background_layer"};
  layers.emplace_back(layer);
}

void AsciiBasicLayerMngr::appendLayer(const Layers &layers) {
  for (const auto &index : layers) {
    this->layers.emplace_back(index);
  }
}

void AsciiBasicLayerMngr::deleteLayer(const std::string &name) {
  if (!isExistLayer(name)) {
    throw AsciiBasicException(__FUNC__, "确定name是否正确，不存在该图层!");
  }
  const int index = getLayerCount(name) - 1;
  layers.erase(layers.begin() + index);
}

void AsciiBasicLayerMngr::insertLayer(int layerCnt,
                                      const AsciiBasicLayer &layer) {
  if (layerCnt <= 0 || layerCnt > layers.size()) {
    throw AsciiBasicException(__FUNC__, "layerCnt不合法!");
  }
  layers.insert(layers.begin() + layerCnt - 1, layer);
}

void AsciiBasicLayerMngr::insertLayer(int layerCnt, const Layers &layers) {
  if (layerCnt <= 0 || layerCnt > layers.size()) {
    throw AsciiBasicException(__FUNC__, "layerCnt不合法!");
  }
  for (int i = 0; i < layers.size(); i++) {
    const auto position = this->layers.begin() + layerCnt - 1 + i;
    this->layers.insert(position, layers[i]);
  }
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas() const {
  static AsciiBasicLayerMngr bffrMngr;
  static AsciiBasicCanvas bffrCnvs;

  if (layers.size() <= 0) {
    throw AsciiBasicException(__FUNC__, "layers的数量<=0!");
  } else if (*this == bffrMngr) {
    return bffrCnvs;
  }

  AsciiBasicCanvas ret = layers[0];
  for (const auto &index : layers) {
    if (!index.isDisplay())
      continue;
    Coord2d coord = index.getCoordinate();
    coord -= index.getCenterCoordinate();
    ret = overlapCanvas(index, ret, coord);
  }

  bffrMngr = *this;
  bffrCnvs = ret;

  return ret;
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas(const std::string &name) const {
  for (const auto &index : layers) {
    if (name == index.getName())
      return index;
  }
  throw AsciiBasicException(__FUNC__, "没有该图层!");
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](const std::string &name) {
  for (auto &index : layers) {
    if (name == index.getName())
      return index;
  }
  appendLayer(AsciiBasicLayer(name));
  return layers[size() - 1];
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) {
  if (index < 0) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  if (index >= layers.size()) {
    for (int i = 0; i < index + 1 - layers.size(); i++) {
      appendLayer(AsciiBasicLayer());
    }
    return layers[index];
  }
  return layers[index];
}

const AsciiBasicLayer &
AsciiBasicLayerMngr::operator[](const std::string &name) const {
  for (const auto &index : layers) {
    if (name == index.getName())
      return index;
  }
  throw AsciiBasicException(__FUNC__, "没有这样的图层");
}

const AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) const {
  if (index < 0 || index >= layers.size()) {
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }
  return layers[index];
}

bool AsciiBasicLayerMngr::operator==(const AsciiBasicLayerMngr &mngr) const {
  return layers == mngr.getLayers();
}

bool AsciiBasicLayerMngr::operator!=(const AsciiBasicLayerMngr &mngr) const {
  return !(layers == mngr.getLayers());
}

AsciiBasicLayer AsciiBasicLayerMngr::getLayer(const std::string &name) const {
  return (*this)[name];
}

void AsciiBasicLayerMngr::setLayer(const AsciiBasicLayer &layer,
                                   const std::string &name) {
  (*this)[name] = layer;
}

void AsciiBasicLayerMngr::setLayer(const AsciiBasicLayer &layer, int index) {
  (*this)[index] = layer;
}

bool AsciiBasicLayerMngr::isExistLayer(const std::string &name) const {
  for (const auto &index : layers) {
    if (name == index.getName())
      return true;
  }
  return false;
}

int AsciiBasicLayerMngr::getLayerCount(const std::string &name) const {
  for (int i = 0; i < layers.size(); i++) {
    if (name == layers[i].getName()) {
      return i;
    }
  }
  throw AsciiBasicException(__FUNC__, "指定名称的图层不存在!");
}
} // namespace AsciiGL