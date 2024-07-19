#include "Log.h"

Log::Log(LogMode mode, const std::string &path) {
  this->mode = mode;
  this->path = path;
}

Log::~Log() {
  std::fstream writer(path);

  if (!writer.is_open()) {
    std::cout << "无法打开文件!" << std::endl;
    exit(-1);
  }

  switch (mode) {
  case File:
  case FileAndDisplay:
    for (const auto &index : logs) {
      writer << index;
    }
    break;
  default:
    std::cout << "deafult bug!" << std::endl;
    exit(-1);
  }
}

void Log::log(const std::string &str, int line, const std::string &path) {
  std::string logInfo;
  logInfo = path + "\t" + std::to_string(line) + "\t" + str;

  switch (mode) {
  case File:
    logs.emplace_back(logInfo);
    break;
  case SimpleDisplay:
    std::cout << str << std::endl;
    break;
  case SpecificDisplay:
    std::cout << logInfo << std::endl;
    break;
  case FileAndDisplay:
    logs.emplace_back(logInfo);
    std::cout << str << std::endl;
    break;
  default:
    std::cout << "deafult bug!" << std::endl;
    exit(-1);
    break;
  }
}

void Log::list() const {
  for (const auto &index : logs) {
    std::cout << index << std::endl;
  }
}