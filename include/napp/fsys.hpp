#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace nlc {
namespace fsys {
struct DirEntry {
  std::string name = "";
  std::string path = "";
  size_t size = 0;
  bool _is_dir = false;
};

std::string GetParentPath(std::string path, std::string mount_point);
std::vector<nlc::fsys::DirEntry>
GetDirContentsExt(std::string &path,
                  const std::vector<std::string> &extensions);
std::vector<nlc::fsys::DirEntry> GetDirContents(std::string &path);
} // namespace fsys
} // namespace nlc