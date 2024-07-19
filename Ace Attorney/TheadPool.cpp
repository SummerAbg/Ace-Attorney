#include "TheadPool.h"

ThreadPool::ThreadPool(int threadCount) {
  this->threadCount = threadCount;
  this->isStop = false;
  for (int i = 0; i < threadCount; i++) {
    workers.emplace_back([&]() {
      while (1) {
        Task task;
        {
          std::unique_lock<std::mutex> lock(mtx);
          cv.wait(lock, [&]() { return isStop || !tasks.empty(); });
          if (isStop && tasks.empty()) {
            return;
          }
          task = tasks.front();
          tasks.pop();
        }
        task();
      }
    });
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(mtx);
    isStop = true;
  }
  cv.notify_all();
  for (auto &thread : workers) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void ThreadPool::addTask(const std::function<void()> &func) {
  {
    std::unique_lock<std::mutex> lock(mtx);
    tasks.push(func);
  }
  cv.notify_one();
}