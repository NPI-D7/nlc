#include <3ds.h>
#include <iostream>
#include <map>
#include <napp/worker.hpp>
#include <nuseful/stringtools.hpp>

std::map<std::string, Thread *> tasks;

namespace nlc {
namespace worker {
void push(void (*task)(void), std::string name) {
  std::string __name = nlc::st::ToLowerCase(name);
  s32 prio = 0;
  svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
  Thread thrd =
      threadCreate((ThreadFunc)task, NULL, 64 * 1024, prio - 1, -2, false);
  tasks.insert(std::make_pair(__name, &thrd));
}
std::vector<std::string> GetTasks() {
  std::vector<std::string> temp;
  for (auto const &it : tasks) {
    temp.push_back(it.first);
  }
  return temp;
}
void kill(std::string task) {
  if (tasks.contains(nlc::st::ToLowerCase(task))) {
    threadJoin(tasks.at(nlc::st::ToLowerCase(task))[0], U64_MAX);u
    threadFree(tasks.at(nlc::st::ToLowerCase(task))[0]);
  }
}
void exit() {
  for (auto const &it : tasks) {
    threadJoin(it.second[0], U64_MAX);
    threadFree(it.second[0]);
  }
}

void sleep(int ms) { svcSleepThread(1000000 * ms); }
} // namespace worker
} // namespace nlc