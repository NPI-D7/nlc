#include <fstream>
#include <nconfig/nconfig.hpp>

namespace nlc {
nconfig::nconfig(int configversion) { tmp_configver = configversion; }

nconfig::~nconfig() { this->Save(); }

void nconfig::Load(std::string path) {
  std::ifstream f(path, std::ios::in);
  if (!f) {
    std::ofstream ff(path);
    ff << "";
    ff.close();
    m_path = path;
  }
  if (f) {
    f >> m_js;
    m_path = path;
  }
  f.close();
}

void nconfig::PrepareRenew() { m_js.clear(); }

void nconfig::Save() {
  if (m_path != "") {
    std::ofstream f(m_path);
    f << m_js.dump(4);
    f.close();
  }
}

bool nconfig::IsValidVersion() {
  if (m_js["nlc_nconfig"].contains("config_version")) {
    if (m_js["nlc_nconfig"]["config_version"].get<int>() == tmp_configver) {
      return true;
    }
  }
  return false;
}

void nconfig::UpdateVersion(int ver) {
  m_js["nlc_nconfig"]["config_version"] = ver;
}

void nconfig::Set(std::string reg, nlc::parameter val) {
  if (val.is<int>()) {
    m_js[reg] = val.get<int>();
  } else if (val.is<float>()) {
    m_js[reg] = val.get<float>();
  } else if (val.is<double>()) {
    m_js[reg] = val.get<double>();
  } else if (val.is<std::string>()) {
    m_js[reg] = val.get<std::string>();
  } else if (val.is<const char *>()) {
    m_js[reg] = val.get<const char *>();
  } else {
    m_js[reg] = "val is not valid";
  }
}
} // namespace nlc