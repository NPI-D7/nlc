#include <map>
#include <nuseful/color.hpp>
#include <nuseful/stringtools.hpp>

namespace nlc {
namespace color_storage {
std::map<std::string, uint32_t> colors_storage;
bool Add(color_t col, std::string register_id) {
  std::string reg = nlc::st::ToLowerCase(register_id);
  if (!colors_storage.contains(reg)) {
    colors_storage.insert(std::make_pair(reg, col.GetRGBA()));
  } else {
    return true;
  }
  return false;
}
uint32_t Get(std::string reg) {
  std::string register_id = nlc::st::ToLowerCase(reg);
  if (colors_storage.contains(register_id)) {
    return colors_storage.at(register_id);
  }
  return 0x00000000;
}
} // namespace color_storage
} // namespace nlc