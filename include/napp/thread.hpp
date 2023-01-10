#pragma once
#include <atomic>
#include <functional>
#include <nuseful/parameter.hpp>
#include <string>

#define THREAD_STACK_SIZE 0x1000

namespace nlc {

class thread {
public:
  thread();
  thread(std::function<void(nlc::parameter)> t_function,
         nlc::parameter t_parameter = nullptr, bool t_autostart = false,
         bool t_detached = false,
         unsigned long long int t_stackSize = 4 * 1024);
  virtual ~thread();
  void initialize(std::function<void(nlc::parameter)> t_function,
                  nlc::parameter t_parameter = nullptr,
                  bool t_autostart = false, bool t_detached = false,
                  unsigned long long int t_stackSize = 4 * 1024);

  void setStackSize(unsigned long long int t_stackSize);

  void start(bool t_detached = false);

  void kill();

  void join(long long unsigned int t_timeout = UINT64_MAX);

  bool isRunning();

  static void sleep();

  void thread::sleep(int t_milliseconds);

private:
  struct threadData {
    nlc::parameter m_parameter;
    std::function<void(nlc::parameter)> m_function;
    std::atomic<bool> *m_running;
  };

  static void threadFunction(void *t_arg);
  /* data */
  int m_priority, m_stackSize;
  bool m_started;
  std::atomic<bool> m_running;
  nlc::thread::threadData m_data;
  int m_thread;
};
} // namespace nlc