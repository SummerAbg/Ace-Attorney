/**
 *
 *  @file      agl_Basic.h
 *  @brief     包括基本函数的全部声明和部分实现
 *  @details   ~
 *  @author    0xZed_
 *  @date      19.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "at_Tools.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#endif

using namespace AsciiTools;

/**
 *  @namespace AsciiGL
 *  @brief     AsciiGL命名空间，包括AsciiGL的基本声明和实现
 *  @author    0xZed_
 */
namespace AsciiGL {
/////////////////////////////////////////////////////////////////

/**
 *  @brief  根据两个坐标的斜率获得一次函数的值
 *  @param  coordA - 坐标1
 *  @param  coordB - 坐标2
 *  @param  x      - 自变量
 *  @retval        - 因变量
 */
double getY(Coord2d coordA, Coord2d coordB, double x);

/**
 *  @brief  获取容器指定元素的下标(成功了返回元素下标，失败了返回0)
 *  @tparam T       - 指定元素类型
 *  @param  vec     - vector容器
 *  @param  element - 指定元素
 *  @retval         - 指定元素的下标
 */
template <typename T> int getIndex(const std::vector<T> &vec, const T &element);

/**
 *  @brief  判断容器是否存在指定元素
 *  @tparam T       - 指定元素类型
 *  @param  vec     - vector容器
 *  @param  element - 指定元素
 *  @retval         - 是否存在该元素的布尔值
 */
template <typename T> bool isExist(const std::vector<T> &vec, const T &element);

/**
 *  @brief  获取名字/取名器(随着名字重复而添加编号)
 *  @brief  请谨慎使用，若在死循环中一直调用这个函数，会导致程序运行效率逐渐低下
 *  @param  prefix - 字符串前缀
 *  @retval        - 自动处理过的标识符/名字
 */
std::string makeName(const std::string &prefix);

/**
 *  @brief  将字符串长度等价转换为Block（块）的个数
 *  @param  strSize     - 字符串长度
 *  @param  blockLength - 块长度
 *  @retval             - 块个数
 */
int getBlockNumber(size_t strSize, size_t blockLength);

/**
 *  @brief  获取文件数据
 *  @param  path - 文件路径
 *  @retval      - 文件数据字符串
 */
std::string getFileData(const std::string &path);

template <typename T>
inline int getIndex(const std::vector<T> &vec, const T &element) {
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == element)
      return i;
  }
  return 0;
}

template <typename T>
inline bool isExist(const std::vector<T> &vec, const T &element) {
  for (const auto &index : vec) {
    if (index == element)
      return true;
  }
  return false;
}
} // namespace AsciiGL