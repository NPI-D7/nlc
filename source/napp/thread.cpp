#include <3ds.h>
#include <napp/thread.hpp>

namespace nlc {

thread::thread() : m_started(false), m_running(false) { /* do nothing */
}

thread::thread(std::function<void(nlc::parameter)> t_function,
               nlc::parameter t_parameter, bool t_autostart, bool t_detached,
               unsigned long long int t_stackSize)
    : m_started(false), m_running(false) {
  initialize(t_function, t_parameter, t_autostart, t_detached, t_stackSize);
}

thread::~thread() {
  join();

  if (m_started)
    threadFree(m_thread);
}

void thread::initialize(std::function<void(nlc::parameter)> t_function,
                        nlc::parameter t_parameter, bool t_autostart,
                        bool t_detached, unsigned long long int t_stackSize) {
  m_stackSize = t_stackSize;
  m_data.m_parameter = t_parameter;
  m_data.m_function = t_function;
  m_data.m_running = &m_running;

  if (t_autostart) {
    start(t_detached);
  }
}

void thread::setStackSize(unsigned long long int t_stackSize) {
  m_stackSize = t_stackSize;
}

void thread::start(bool t_detached) {
  if (!m_running) {
    m_started = true;
    m_running = true;
    s32 prio;
    svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
    m_thread = threadCreate(threadFunction, &m_data, m_stackSize, prio + 1, -2,
                            t_detached);
  }
}

void thread::kill() {
  threadDetach(m_thread);
  m_running = false;
  m_started = false;
}

void thread::join(long long unsigned int t_timeout) {
  if (m_running) {
    threadJoin(m_thread, t_timeout);
    threadFree(m_thread);
    m_running = false;
    m_started = false;
  }
}

bool thread::isRunning() { return m_running; }

void thread::sleep() { svcSleepThread(0); }

void thread::sleep(int t_milliseconds) {
  svcSleepThread(1000000 * t_milliseconds);
}

// private methods
void thread::threadFunction(void *arg) {
  nlc::thread::threadData data = *static_cast<nlc::thread::threadData *>(arg);
  data.m_function(data.m_parameter);
  *data.m_running = false;
}
} // namespace nlc