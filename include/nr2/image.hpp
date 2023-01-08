#pragma once
#include <string>
#include <vector>

namespace nlc {
class image {
private:
  int regid = 0;
  bool loadet = false;

public:
  image();
  ~image();
  void LoadFile(std::string path);
  void LoadBuffer(std::vector<unsigned char *> buffer);
  int GetReg();
};
} // namespace nlc