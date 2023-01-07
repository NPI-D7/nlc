#include <3ds.h>
#include <iostream>
#include <napp/worker.hpp>
#include <nuseful/stringtools.hpp>

struct w_Task {
  std::string name;
  Thread thrd;
};

std::vector<w_Task> tasks;

namespace nlc {
namespace worker {
void push(void (*task)(void), std::string name) {
  w_Task temp;
  temp.name = nlc::st::ToLowerCase(name);
  s32 prio = 0;
  svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
  temp.thrd =
      threadCreate((ThreadFunc)task, NULL, 64 * 1024, prio - 1, -2, false);
  tasks.push_back(temp);
}
std::vector<std::string> GetTasks() {
  std::vector<std::string> temp;
  for (auto const &it : tasks) {
    temp.push_back(it.name);
  }
  return temp;
}
void kill(std::string task) {
  for (auto const &it : tasks) {
    if (it.name == nlc::st::ToLowerCase(task)) {
      threadJoin(it.thrd, U64_MAX);
      threadFree(it.thrd);
    }
  }
}
void exit() {
  for (auto const &it : tasks) {
    threadJoin(it.thrd, U64_MAX);
    threadFree(it.thrd);
  }
}
} // namespace worker
} // namespace nlc