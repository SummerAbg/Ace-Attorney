#pragma once
#pragma comment(lib, "irrKlang.lib")

#include "AsciiGL/include/graphics.h"
#include "Log.h"
#include "irrKlang/include/irrKlang.h"
#include <chrono>
#include <conio.h>
#include <functional>
#include <shared_mutex>

namespace AceAttorney {
const double goldenRatio = 0.618;

const int fontSize = 30;

const int gameLength = 30;
const int gameWidth = 29;

const std::wstring windowTitle = L"Ace Attorney";
const std::wstring windowFont = L"Terminal";

extern Log *gameLog;

// 初始化AsciiGL
void initAsciiGL();

// 初始化WindowRGB
void initWindowRGB();

// 获取帧率
// double getFPS();
int getFPS(int deltaTime);

// 设置字体
void setFont(int size = fontSize);

// 设置窗口大小
void setWindowSize(int length = gameLength * TRPRSTR.size(),
                   int width = gameWidth);

// 初始化Window
void initWindow(int length = gameLength, int width = gameWidth);

// 读取文件
std::string readFile(const std::string &path);

// 时间测量类
class TimeMeasurer {
public:
  typedef std::chrono::steady_clock::time_point Time_point;

  TimeMeasurer(std::atomic_int *ret) {
    if (ret != NULL) {
      this->ret = ret;
      startTime = std::chrono::high_resolution_clock().now();
    } else {
      gameLog->log("空指针!");
      exit(-1);
    }
  }
  ~TimeMeasurer() {
    endTime = std::chrono::high_resolution_clock().now();
    (*ret).store((int)std::chrono::duration_cast<std::chrono::milliseconds>(
                     endTime - startTime)
                     .count());
  }

private:
  Time_point startTime;
  Time_point endTime;
  std::atomic_int *ret;
};

class Task {
public:
  using Function = std::function<void()>;
  using pFunction = std::shared_ptr<Function>;

  Task() = default;
  Task(const Function &func, bool rallState = true) {
    this->func = std::make_shared<Function>(func);
    this->rallState = rallState;
    if (rallState) {
      mtx.lock();
    }
  }
  Task(const Task &task) {
    this->func = std::make_shared<Function>(*task.getFunc());
    this->rallState = task.isRall();
    if (rallState) {
      mtx.lock();
    }
  }
  ~Task() {
    if (rallState) {
      (*func)();
      mtx.unlock();
    }
  }

  void operator=(const Task &task) {
    this->func = std::make_shared<Function>(*task.getFunc());
    this->rallState = task.isRall();
  }

  void operator()() {
    if (!rallState) {
      std::unique_lock<std::mutex> lock(mtx);
      (*func)();
    } else {
      (*func)();
    }
  }

  pFunction getFunc() const { return func; }
  bool isRall() const { return rallState; }

private:
  pFunction func;
  std::mutex mtx;
  bool rallState;
};
} // namespace AceAttorney