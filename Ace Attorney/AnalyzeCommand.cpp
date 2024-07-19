#include "AnalyzeCommand.h"

AceAttorney::AnalyzeCommand::AnalyzeCommand(const std::string &str) {
  if (str.size() <= 0) {
    gameLog->log("str太短!");
    exit(-1);
  }
  auto tokens = split(str, ' ');
  if (tokens.size() < 1) {
    gameLog->log("token太少!");
    exit(-1);
  }
  command = tokens[0];
  for (int i = 1; i < tokens.size(); i++) {
    options.emplace_back(tokens[i]);
  }
}

AceAttorney::AnalyzeCommand::AnalyzeCommand(const Option &options) {
  this->options = options;
}

AceAttorney::Option AceAttorney::AnalyzeCommand::getOptions() const {
  return options;
}

AceAttorney::Option AceAttorney::AnalyzeCommand::getOptions(int begin,
                                                            int end) const {
  if (begin <= 0 || begin > options.size() || end <= 0 ||
      end > options.size() || begin >= end) {
    gameLog->log("begin或end的值非法!");
  }
  Option ret;
  for (int i = begin - 1; i <= end; i++) {
    ret.emplace_back(options[i]);
  }
  return ret;
}

std::string AceAttorney::AnalyzeCommand::operator[](int index) const {
  if (index < 0 || index > options.size()) {
    gameLog->log("index非法!");
    exit(-1);
  }
  return options[index];
}

std::string AceAttorney::AnalyzeCommand::getOption(int index) const {
  if (index < 0 || index >= options.size()) {
    gameLog->log("index非法!");
    exit(-1);
  }
  return options[index];
}

size_t AceAttorney::AnalyzeCommand::getOptionsSize() const {
  return options.size();
}

std::string AceAttorney::AnalyzeCommand::getCommand() const { return command; }

bool AceAttorney::AnalyzeCommand::isExistOptions() const {
  return options.size() != 0 ? true : false;
}