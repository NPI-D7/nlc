#pragma once
#include <napp/fsys.hpp>
#include <napp/ntrace.hpp>
#include <napp/scene.hpp>
#include <napp/time.hpp>
#include <napp/worker.hpp>
#include <string>

namespace nlc {
class napp {
public:
  napp(std::string name = "nlc_app");
  ~napp();
  bool Running();
  void ForceKill();
  std::string GetSysLangKey();
  void InitNdsp();
  bool IsNdspLoadet() { return isNdsp; }

private:
  std::string m_lc_name;
  bool m_exit = false;
  bool isNdsp = false;
};
} // namespace nlc