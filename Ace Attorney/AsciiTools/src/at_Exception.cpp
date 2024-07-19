#include "at_Exception.h"

namespace AsciiTools {
AsciiBasicException::AsciiBasicException(const std::string &where,
                                         const BasicException &error) {
  this->where = where;
  this->error = error;
  this->error_str = std::string("No describe");
}

AsciiBasicException::AsciiBasicException(const std::string &where,
                                         const std::string &error_str) {
  this->where = where;
  this->error = BasicException();
  this->error_str = error_str;
}

std::string AsciiBasicException::what() const {
  std::string ret;
  ret += "在 " + where + " 中出现了意外的 ";

  switch (error) {
  case CustomError:
    ret += error_str;
    break;

  case FileNotExist:
    ret += "文件不存在!";
    break;

  case FileFormatError:
    ret += "文件格式错误!";
    break;

  case ArrayOverflow:
    ret += "数组溢出!";
    break;

  case NotInitialized:
    ret += "未初始化!";
    break;

  default:
    ret += "BUG!";
    break;
  }
  ret += "\n";
  return ret;
}
} // namespace AsciiTools