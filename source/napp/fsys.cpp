#include <napp/fsys.hpp>
#include <nuseful/stringtools.hpp>

namespace nlc {
namespace fsys {
std::string GetParentPath(std::string path, std::string mount_point) {
  std::string tcl = path;
  if (path.substr(path.length(), 1) != "/") {
    tcl += "/";
  }
  if (std::filesystem::exists(
          std::filesystem::path(tcl).parent_path().parent_path()))
    return std::filesystem::path(tcl).parent_path().parent_path().string();
  return mount_point;
}

std::vector<nlc::fsys::DirEntry>
GetDirContentsExt(std::string &path,
                  const std::vector<std::string> &extensions) {
  std::vector<nlc::fsys::DirEntry> res;
  for (auto const &it :
       std::filesystem::directory_iterator(std::filesystem::path(path))) {

    if (it.is_directory()) {
      nlc::fsys::DirEntry temp;
      temp.name = nlc::st::GetFileName(it.path().string());
      temp.path = it.path().string();
      temp.size = it.file_size();
      temp._is_dir = it.is_directory();
      res.push_back(temp);
    }
    if (nlc::st::NameIsEndingWith(nlc::st::GetFileName(it.path().string()),
                                  extensions)) {
      nlc::fsys::DirEntry temp;
      temp.name = nlc::st::GetFileName(it.path().string());
      temp.path = it.path().string();
      temp.size = it.file_size();
      temp._is_dir = it.is_directory();
      res.push_back(temp);
    }
  }
  return res;
}

std::vector<nlc::fsys::DirEntry> GetDirContents(std::string &path) {
  return GetDirContentsExt(path, {});
}
} // namespace fsys
} // namespace nlc