#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

enum LogMode { File, SimpleDisplay, SpecificDisplay, FileAndDisplay };

// »’÷æ
class Log {
public:
  Log(LogMode mode, const std::string &path = "");
  ~Log();

  void log(const std::string &str, int line = __LINE__,
           const std::string &path = __FILE__);
  void list() const;

private:
  std::string path;
  LogMode mode;
  std::vector<std::string> logs;
};