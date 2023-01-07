#include <napp/time.hpp>
#include <nuseful/stringtools.hpp>
#include <string>
#include <time.h>

namespace nlc {
namespace ntime {
std::string GetTimeStr(void) {
  time_t unixTime;
  struct tm timeStruct;
  time(&unixTime);
  localtime_r(&unixTime, &timeStruct);
  return nlc::st::FormatString("%04i-%02i-%02i_%02i-%02i-%02i",
                               timeStruct.tm_year + 1900, timeStruct.tm_mon + 1,
                               timeStruct.tm_mday, timeStruct.tm_hour,
                               timeStruct.tm_min, timeStruct.tm_sec);
}
} // namespace ntime
} // namespace nlc
