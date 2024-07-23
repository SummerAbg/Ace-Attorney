/**
 *
 *  @file      graphics.h
 *  @brief     包括基本字符串图像操作函数的声明
 *  @details   ~
 *  @author    0xZed_
 *  @date      19.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "agl_BasicLayerMngr.h"

namespace AsciiGL {
/**
 *  @brief  获取指定区域的画布 （失败时抛出异常）
 *  @param  canvas - 指定画布
 *  @param  coordA - 指定坐标A
 *  @param  coordB - 指定坐标B
 *  @retval        - 指定坐标A，B区域内的画布
 */
AsciiBasicCanvas getCanvas(const AsciiBasicCanvas &canvas, Coord2d coordA,
                           Coord2d coordB);

/**
 *  @brief  重叠两个画布
 *  @brief  会将canvas重叠在target的coord坐标上，最终画布大小以target为标准
 *  @param  canvas - 指定画布
 *  @param  target - 目标画布
 *  @param  coord  - 指定坐标
 *  @retval        - 以目标画布为基础的重叠后的画布
 */
AsciiBasicCanvas overlapCanvas(const AsciiBasicCanvas &canvas,
                               const AsciiBasicCanvas &target, Coord2d coord);

/**
 *  @brief 在指定画布下的指定坐标设置文本 （不添加图层,在原有画布进行修改）
 *  @param canvas - 指定画布
 *  @param coord  - 指定坐标
 *  @param str    - 指定文本
 */
void setText(AsciiBasicCanvas &canvas, Coord2d coord,
             const AsciiBasicString &text);

/**
 *  @brief 在指定图层下的指定坐标设置文本 （不添加图层,在原有图层进行修改）
 *  @brief
 * 若单纯设置文本，不推荐使用该函数！建议采用带有画布形参或图层管理器形参的setText函数
 *  @brief 详细说明:当某图层被调用该函数时，图层原有的数据将被覆盖！
 *  @param layer - 指定图层 （图层中画布的长由指定文本的长度决定）
 *  @param coord - 指定坐标
 *  @param text  - 指定文本
 */
void setText(AsciiBasicLayer &layer, Coord2d coord,
             const AsciiBasicString &text);

/**
 *  @brief 在指定图层管理器下的指定坐标设置文本 （添加图层）
 *  @brief 详细说明:当某重名图层被该函数调用时，不进行添加图层的操作
 *  @param mngr      - 指定图层管理器
 *  @param coord     - 指定坐标
 *  @param text      - 指定文本
 *  @param layerName - 文本图层名称
 */
void setText(AsciiBasicLayerMngr &mngr, Coord2d coord,
             const AsciiBasicString &text,
             const std::string &layerName = makeName("textLayer"));

/**
 *  @brief 在指定画布中设置指定字符串的边框（厚度默认为一个控制台字符单位）
 *  @param canvas - 指定画布
 *  @param str    - 指定字符串
 */
void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str);

/**
 *  @brief
 * 比较指定画布在指定坐标下的目标画布重叠后的不同（这要求双方的blockLength要一致！）
 *  @param  target - 目标画布
 *  @param  canvas - 指定画布
 *  @param  coord  - 指定坐标
 *  @retval        - 不同处的坐标
 */
std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas,
                                   Coord2d coord = Vec2d(0, 0));

/**
 *  @brief 在指定画布下的两个指定坐标之间绘制线条
 *  @param canvas - 指定画布
 *  @param coordA - 坐标A
 *  @param coordB - 坐标B
 *  @param str    - 指定字符串
 *  @param level  - 绘制精度（越大越好，不得小于-15）
 */
void setLine(AsciiBasicCanvas &canvas, Coord2d coordA, Coord2d coordB,
             const AsciiBasicString &str, int level = 1);

/**
 *  @brief 倒映画布
 * （指的是将指定画布切割至最小单位宽度的长条后，将从最上方的部分自下往上排列），如：
 *  @brief       ##A##~~>B###A
 *  @brief       #A#A#~~>#A#A#
 *  @brief       B###A~~>##A##
 *  @param canvas -
 */
void reflect(AsciiBasicCanvas &canvas);

#if defined(_WIN64) || defined(_WIN32)
/**
 *  @brief 利用WinAPI缓冲选择性输出画布 （可大大提高性能）
 *  @param canvas  - 指定画布
 *  @param isClean - 是否清空缓冲区
 */
void WinAPIDraw(const AsciiBasicCanvas &canvas, bool isClean = false);

/**
 *  @brief 利用WinAPI缓冲选择性输出图层管理器的合成画布 （可大大提高性能）
 *  @param canvas  - 指定图层管理器
 *  @param isClean - 是否清空缓冲区
 */
void WinAPIDraw(const AsciiBasicLayerMngr &mngr, bool isClear = false);

/**
 *  @brief 隐藏光标
 */
void hideCursor();

#endif
} // namespace AsciiGL