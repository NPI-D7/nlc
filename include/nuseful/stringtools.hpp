#pragma once
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace nlc {
namespace st {
inline std::string ToLowerCase(std::string in) {
  std::transform(in.begin(), in.end(), in.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return in;
}

template <typename T> std::string int2hex(T i) {
  std::stringstream stream;
  stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex
         << i;
  return stream.str();
}
} // namespace st
} // namespace nlc