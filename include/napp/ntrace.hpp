#pragma once

#include <cstdio>

namespace nlc {
namespace ntrace {
typedef struct Counter {
  const char *name_;
  const char *func_;
  double time_ms;
  double time_ms_st;
  double time_ms_en;
} Counter;

typedef struct StartTime {
  const char *name_;
  const char *func_;
  double time_ms_st;
} StartTime;

void init(const char *filename);
void exit(void);
void trace_begin(const char *name, const char *func);
void trace_end(const char *name, const char *func);
void trace_void(void (*Func)(void), const char *name, const char *func);
} // namespace ntrace
} // namespace nlc