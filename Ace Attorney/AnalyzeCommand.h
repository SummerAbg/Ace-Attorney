#pragma once

#include "Resources.h"

namespace AceAttorney {
typedef std::vector<std::string> Option;

// 指令分析类
class AnalyzeCommand {
public:
  AnalyzeCommand(const std::string &str);
  AnalyzeCommand(const Option &options);

  // 获取options
  Option getOptions() const;
  Option getOptions(int begin, int end) const;

  std::string operator[](int index) const;

  // 获取option
  std::string getOption(int index) const;

  // 获取options的个数
  size_t getOptionsSize() const;

  // 获取command
  std::string getCommand() const;

  // 是否存在options
  bool isExistOptions() const;

private:
  std::string command;
  Option options;
};
} // namespace AceAttorney