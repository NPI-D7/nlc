#pragma once
#include <napp/fsys.hpp>
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

private:
  std::string m_lc_name;
  bool m_exit = false;
};
} // namespace nlc