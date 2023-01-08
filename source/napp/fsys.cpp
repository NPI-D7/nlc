#include <algorithm>
#include <napp/fsys.hpp>
#include <nuseful/stringtools.hpp>

bool dirEntryPredicate(const nlc::fsys::DirEntry &lhs,
                       const nlc::fsys::DirEntry &rhs) {
  if (!lhs._is_dir && rhs._is_dir)
    return false;
  if (lhs._is_dir && !rhs._is_dir)
    return true;

  return strcasecmp(lhs.name.c_str(), rhs.name.c_str()) < 0;
}

namespace nlc {
namespace fsys {
std::string GetParentPath(std::string path, std::string mount_point) {
  std::string tcl = path;
  if (path.substr(path.length() - 1, 1) != "/") {
    tcl += "/";
  }
  std::string res;
  if (std::filesystem::exists(
          std::filesystem::path(tcl).parent_path().parent_path()))
    res = std::filesystem::path(tcl).parent_path().parent_path().string();
  if (res.length() > mount_point.length()) {
    return res;
  }

  return mount_point;
}

std::vector<nlc::fsys::DirEntry>
GetDirContentsExt(std::string &path,
                  const std::vector<std::string> &extensions) {
  std::vector<nlc::fsys::DirEntry> res;
  for (auto const &it :
       std::filesystem::directory_iterator(std::filesystem::path(path))) {
    nlc::fsys::DirEntry temp;
    temp.name = nlc::st::GetFileName(it.path().string().c_str());
    temp.path = it.path().string().c_str();
    temp._is_dir = it.is_directory();
    if (nlc::st::NameIsEndingWith(nlc::st::GetFileName(it.path().string()),
                                  extensions) ||
        it.is_directory()) {
      res.push_back(temp);
    }
  }
  std::sort(res.begin(), res.end(), dirEntryPredicate);
  return res;
}

std::vector<nlc::fsys::DirEntry> GetDirContents(std::string &path) {
  return GetDirContentsExt(path, {});
}
} // namespace fsys
} // namespace nlc