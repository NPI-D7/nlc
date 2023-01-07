#pragma once
#include <nuseful/json.hpp>
#include <nuseful/parameter.hpp>
#include <string>

namespace nlc {
class nconfig {
public:
  nconfig(int configversion);
  ~nconfig();
  void Load(std::string path);
  bool IsValidVersion();
  void UpdateVersion(int ver);
  void PrepareRenew();
  void Save();
  void Set(std::string reg, nlc::parameter val);
  int GetInt(std::string reg) { return m_js[reg].get<int>(); }
  float GetFloat(std::string reg) { return m_js[reg].get<float>(); }
  std::string GetString(std::string reg) {
    return m_js[reg].get<std::string>();
  }
  double GetDouble(std::string reg) { return m_js[reg].get<double>(); }

private:
  std::string m_path;
  nlohmann::json m_js;
  int tmp_configver;
};
} // namespace nlc