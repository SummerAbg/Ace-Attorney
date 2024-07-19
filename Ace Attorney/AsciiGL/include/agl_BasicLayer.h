/**
 *
 *  @file      agl_BasicLayer.h
 *  @brief     包括基本字符串图层类的实现
 *  @details   ~
 *  @author    0xZed_
 *  @date      19.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "agl_BasicCanvas.h"

namespace AsciiGL {
/**
 *
 *  @class   AsciiBasicLayer
 *  @brief   基本字符串图层
 *  @details
 * ~继承了基本字符串图层类，并添加了对图层坐标、中心坐标、图层名字、显示状态的操作
 *  @date    19.07.2024
 *
 */
class AsciiBasicLayer : public AsciiBasicCanvas {
public:
  /**
   *  @brief AsciiBasicLayer object constructor
   */
  AsciiBasicLayer();

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param canvas - 指定画布
   *  @param coord  - 图层坐标
   */
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coord2d coord);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param canvas       - 指定画布
   *  @param coord        - 图层坐标
   *  @param name         - 图层名称
   *  @param displayState - 显示状态
   */
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coord2d coord,
                  const std::string &name, bool displayState = true);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param name - 图层名称
   */
  AsciiBasicLayer(const std::string &name);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param layer - 图层
   */
  AsciiBasicLayer(const AsciiBasicLayer &layer);

  /**
   *  @brief 设置图层中画布的坐标
   *  @param coord - 指定坐标
   */
  void setCoordinate(Coord2d coord) { this->coord = coord; }

  /**
   *  @brief  获取图层中画布的坐标
   *  @retval  - 图层坐标
   */
  Coord2d getCoordinate() const { return coord; }

  /**
   *  @brief 设置图层中画布的中心坐标
   *  @param coord - 指定坐标
   */
  void setCenterCoordinate(Coord2d coord);

  /**
   *  @brief  获取图层中画布的中心坐标
   *  @retval  - 中心坐标
   */
  Coord2d getCenterCoordinate() const { return centerCoord; }

  /**
   *  @brief 设置图层名称
   *  @param name - 指定名称
   */
  void setName(const std::string &name) { this->name = name; }

  /**
   *  @brief  获取图层名称
   *  @retval  - 图层名称
   */
  std::string getName() const { return name; }

  /**
   *  @brief 设置图层的显示状态
   *  @param displayState - 显示状态的布尔值
   */
  void setDisplayState(bool displayState) { this->displayState = displayState; }

  /**
   *  @brief  获取图层的显示状态
   *  @retval  - 显示状态的布尔值
   */
  bool isDisplay() const { return displayState; }

  virtual bool operator==(const AsciiBasicLayer &layer) const;
  virtual bool operator!=(const AsciiBasicLayer &layer) const;

private:
  Coord2d coord;    // 坐标
  std::string name; // 名称
  Coord2d centerCoord; // 中心坐标(相对于画布左上角为原点的相对坐标)
  bool displayState; // 显示状态
};
} // namespace AsciiGL