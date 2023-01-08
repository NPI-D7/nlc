#include <3ds.h>
#include <fstream>
#include <napp/ntrace.hpp>
#include <vector>

#define TICKS_PER_MSEC 268111.856

namespace nlc {
namespace ntrace {

std::ofstream fpc;

std::vector<StartTime> startcnt;

void init(const char *filename) {
  fpc.open(filename, std::ios::app);
  if (fpc)
    fpc << "\nNAME,FUNCTION,TIME(MS),REGID\n";
}

void exit(void) {
  if (fpc)
    fpc.close();
}

void trace_begin(const char *name, const char *func) {
  StartTime strt__;
  strt__.func_ = func;
  strt__.name_ = name;
  strt__.time_ms_st = osGetTime();
  startcnt.push_back(strt__);
}

void trace_end(const char *name, const char *func) {
  double strttt = 0;
  int regid = 0;
  for (size_t i = 0; i < startcnt.size(); i++) {
    if (startcnt[i].name_ == name && startcnt[i].func_ == func) {
      strttt = startcnt[i].time_ms_st;
      regid = i;
      startcnt.erase(startcnt.begin() + i);
    }
  }
  Counter cntr;
  cntr.func_ = func;
  cntr.name_ = name;
  cntr.time_ms_st = strttt;
  cntr.time_ms_en = (double)osGetTime();
  cntr.time_ms = cntr.time_ms_en - cntr.time_ms_st;
  char buf[52];
  sprintf(buf, "%s,%s,%f,%d\n", cntr.name_, cntr.func_, cntr.time_ms, regid);
  if (fpc)
    fpc << buf;
}

void trace_void(void (*Func)(void), const char *name, const char *func) {
  trace_begin(name, func);
  Func();
  trace_end(name, func);
}

} // namespace ntrace
} // namespace nlc