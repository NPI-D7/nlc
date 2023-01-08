#include <fstream>
#include <unistd.h>
#include <nconfig/lang.hpp>

static nlohmann::json appJson;

namespace nlc {
namespace lang {
std::string get(const std::string &key) {
  if (!appJson.contains(key))
    return key;

  return appJson.at(key).get_ref<const std::string &>();
}

void load(const std::string &lang) {
  FILE *values;

  if (access(("romfs:/lang/" + lang + "/app.json").c_str(), F_OK) == 0) {
    values = fopen(("romfs:/lang/" + lang + "/app.json").c_str(), "rt");
    if (values) {
      appJson = nlohmann::json::parse(values, nullptr, false);
      fclose(values);
    }
    if (appJson.is_discarded())
      appJson = {};
    return;

  } else {
    values = fopen("romfs:/lang/en/app.json", "rt");
    if (values) {
      appJson = nlohmann::json::parse(values, nullptr, false);
      fclose(values);
    }
    if (appJson.is_discarded())
      appJson = {};
    return;
  }
}
} // namespace lang
} // namespace nlc