#pragma once

#include <string>
#include <vector>

namespace nlc {
namespace worker {
void push(void (*task)(void), std::string name);
std::vector<std::string> GetTasks();
void kill(std::string task);
void exit();
void sleep(int ms);
} // namespace worker
} // namespace nlc