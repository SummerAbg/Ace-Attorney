/**
 *
 *  @file      agl_AbstractImage.h
 *  @brief     包括图像抽象类的声明
 *  @details   ~
 *  @author    0xZed_
 *  @date      20.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "at_BasicString.h"
#include "at_Matrix2d.h"

using namespace AsciiTools;

namespace AsciiGL {
/**
 *
 *  @class   AbstractImage
 *  @brief   图像抽象类
 *  @details ~具体声明了图像抽象类的接口
 *  @tparam  DataType - 图像数据类型
 *  @date    20.07.2024
 *
 */
template <typename DataType> class AbstractImage : public Matrix2d<DataType> {
public:
  /**
   *  @brief 存储图像文件至指定文件路径
   *  @param path - 指定图像文件路径
   */
  virtual void save(const std::string &path) const = 0;

  /**
   *  @brief 加载指定路径的图像文件
   *  @param path - 指定图像文件路径
   */
  virtual void load(const std::string &path) = 0;
};
} // namespace AsciiGL