#pragma once

#include "at_Basic.h"
#include <iostream>

namespace AsciiTools {
// 基本错误
enum BasicException {
  CustomError,     // 自定义错误
  FileNotExist,    // 文件不存在
  FileFormatError, // 文件格式错误
  ArrayOverflow,   // 数组溢出
  NotInitialized   // 未初始化
};

// 基本错误类
class AsciiBasicException {
public:
  // 构造基本错误
  AsciiBasicException() = default;
  AsciiBasicException(const std::string &where, const BasicException &error);
  AsciiBasicException(const std::string &where, const std::string &error_str);

  // 获取错误
  std::string what() const;

private:
  std::string where;     // 哪里出错
  BasicException error;  // 错误类型
  std::string error_str; // 错误字符串
};
} // namespace AsciiTools