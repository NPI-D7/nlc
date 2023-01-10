#pragma once
#include <3ds.h>
#include <atomic>
#include <functional>
#include <nuseful/parameter.hpp>
#include <string>

using CTRU_Thread = Thread;

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
  void join(long long unsigned int t_timeout = U64_MAX);
  bool isRunning();
  static void sleep();
  static void sleep(int t_milliseconds);

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
  CTRU_Thread m_thread;
};
} // namespace nlc