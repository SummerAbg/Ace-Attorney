#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

typedef std::function<void()> Task;

class ThreadPool {
public:
  ThreadPool() = default;
  ThreadPool(int threadCount);
  ~ThreadPool();

  void addTask(const std::function<void()> &func);

private:
  std::vector<std::thread> workers;
  std::queue<Task> tasks;
  int threadCount;
  std::mutex mtx;
  std::condition_variable cv;
  bool isStop;
};