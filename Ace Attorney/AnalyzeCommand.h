#pragma once

#include "Resources.h"

namespace AceAttorney {
typedef std::vector<std::string> Option;

// ָ�������
class AnalyzeCommand {
public:
  AnalyzeCommand(const std::string &str);
  AnalyzeCommand(const Option &options);

  // ��ȡoptions
  Option getOptions() const;
  Option getOptions(int begin, int end) const;

  std::string operator[](int index) const;

  // ��ȡoption
  std::string getOption(int index) const;

  // ��ȡoptions�ĸ���
  size_t getOptionsSize() const;

  // ��ȡcommand
  std::string getCommand() const;

  // �Ƿ����options
  bool isExistOptions() const;

private:
  std::string command;
  Option options;
};
} // namespace AceAttorney