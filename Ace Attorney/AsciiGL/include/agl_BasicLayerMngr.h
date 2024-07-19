/**
 *
 *  @file      agl_BasicLayerMngr.h
 *  @brief     包括基本字符串图层管理器类的实现
 *  @details   ~
 *  @author    0xZed_
 *  @date      19.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "agl_BasicLayer.h"

namespace AsciiGL {
/**
 *
 *  @class   AsciiBasicLayerMngr
 *  @brief   基本字符串图层管理器类
 *  @details ~实现了包括管理图层、操作图层以及获取管理器信息的功能
 *  @date    19.07.2024
 *
 */
class AsciiBasicLayerMngr {
public:
  using Layers = std::vector<AsciiBasicLayer>;

  /**
   *  @brief AsciiBasicLayerMngr object constructor
   */
  AsciiBasicLayerMngr() = default;

  /**
   *  @brief AsciiBasicLayerMngr object constructor
   *  @param layers - 指定图层容器
   */
  AsciiBasicLayerMngr(const Layers &layers) { this->layers = layers; }

  /**
   *  @brief AsciiBasicLayerMngr object constructor
   *  @param length - 管理器合成画布的长度
   *  @param width  - 管理器合成画布的宽度
   *  @param str    - 默认填充字符串
   */
  AsciiBasicLayerMngr(int length, int width,
                      const AsciiBasicString &str = TRPRSTR);

  /**
   *  @brief  Return iterator to beginning
   *  @retval  - iterator to beginning
   */
  auto begin() const { return layers.begin(); }

  /**
   *  @brief  Return iterator to end
   *  @retval  - iterator to end
   */
  auto end() const { return layers.end(); }

  /**
   *  @brief 添加指定图层
   *  @param layer - 指定图层
   */
  void appendLayer(const AsciiBasicLayer &layer) { layers.emplace_back(layer); }

  /**
   *  @brief 添加指定图层
   *  @param layers - 图层容器
   */
  void appendLayer(const Layers &layers);

  /**
   *  @brief 删除指定图层 (失败时抛出异常)
   *  @param name - 指定图层名称
   */
  void deleteLayer(const std::string &name);

  /**
   *  @brief 在指定位置后插入指定图层 (失败时抛出异常)
   *  @param layerCnt - 指定位置
   *  @param layer    - 指定图层
   */
  void insertLayer(int layerCnt, const AsciiBasicLayer &layer);

  /**
   *  @brief 在指定位置后插入指定图层容器 (失败时抛出异常)
   *  @param layerCnt - 指定位置
   *  @param layers   - 指定图层容器
   */
  void insertLayer(int layerCnt, const Layers &layers);

  /**
   *  @brief  获取多图层合并后生成的画布 (失败时抛出异常)
   *  @retval  - 合成后的基本字符串画布
   */
  AsciiBasicCanvas getCanvas() const;

  /**
   *  @brief  获取指定名称的画布 (失败时抛出异常)
   *  @param  name - 指定图层名称
   *  @retval      - 指定名称的画布
   */
  AsciiBasicCanvas getCanvas(const std::string &name) const;

  /**
   *  @brief  获取/修改指定名称的图层 （失败时创建并返回空图层）
   *  @param  name - 指定图层名称
   *  @retval      - 指定图层的引用
   */
  AsciiBasicLayer &operator[](const std::string &name);

  /**
   *  @brief  获取/修改指定编号的图层 （失败时抛出异常）
   *  @param  index - 指定编号
   * （若编号大于等于管理器图层数，则创建并返回新的空图层）
   *  @retval       - 指定编号的图层
   */
  AsciiBasicLayer &operator[](int index);

  /**
   *  @brief  获取指定名称的图层 （失败时抛出异常）
   *  @param  name - 指定图层名称
   *  @retval      - 指定名称的图层
   */
  const AsciiBasicLayer &operator[](const std::string &name) const;

  /**
   *  @brief  获取指定图层的图层 （失败时抛出异常）
   *  @param  index - 指定编号
   *  @retval       - 指定编号的图层
   */
  const AsciiBasicLayer &operator[](int index) const;

  bool operator==(const AsciiBasicLayerMngr &mngr) const;
  bool operator!=(const AsciiBasicLayerMngr &mngr) const;

  /**
   *  @brief  获取指定名称的图层 （失败时抛出异常）
   *  @param  name - 指定图层名称
   *  @retval      - 指定名称的图层
   */
  AsciiBasicLayer getLayer(const std::string &name) const;

  /**
   *  @brief  获取指定编号的图层 （失败时抛出异常）
   *  @param  index - 指定编号
   *  @retval       - 指定编号的图层
   */
  AsciiBasicLayer getLayer(int index) const { return layers[index]; }

  /**
   *  @brief 设置指定名称的图层 （失败时抛出异常）
   *  @param layer - 指定图层
   *  @param name  - 指定图层名称
   */
  void setLayer(const AsciiBasicLayer &layer, const std::string &name);

  /**
   *  @brief 设置指定编号的图层 （失败时抛出异常）
   *  @param layer - 指定编号
   *  @param name  - 指定编号名称
   */
  void setLayer(const AsciiBasicLayer &layer, int index);

  /**
   *  @brief  获取管理器图层数
   *  @retval  - 图层数
   */
  int size() const { return static_cast<int>(layers.size()); }

  /**
   *  @brief  获取管理器图层容器
   *  @retval  - 包括着所有图层的图层容器
   */
  Layers getLayers() const { return layers; }

  /**
   *  @brief  判断是否存在指定名称的图层
   *  @param  name - 指定图层名称
   *  @retval      - 是否存在指定名称图层的布尔值
   */
  bool isExistLayer(const std::string &name) const;

  /**
   *  @brief  获取指定图层所在层数 （失败时抛出异常）
   *  @param  name - 指定图层名称
   *  @retval      - 指定名称的图层所在层数
   */
  int getLayerCount(const std::string &name) const;

private:
  Layers layers;
};
} // namespace AsciiGL