#pragma once

#include "at_Coordinate2d.h"
#include "at_Exception.h"
#include "at_TextColor.h"
#include <iostream>
#include <string>
#include <vector>

namespace AsciiTools {
#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__ __PRETTY_FUNCTION__
#endif

typedef Coordinate2d<int> Vec2d;
typedef Coordinate2d<int> Coord2d;

using Point2D = Coord2d;                                // 二维点坐标
using AsciiTrprData = std::vector<bool>;                // 透明数据
using AsciiColorData = std::vector<AsciiColor>;         // 颜色数据
using AsciiTextColorData = std::vector<AsciiTextColor>; // 文本颜色数据
} // namespace AsciiTools