#include <napp/napp.hpp>
#include <nuseful/stringtools.hpp>

#include <3ds.h>

namespace nlc {
napp::napp(std::string name) {
  this->m_lc_name = nlc::st::ToLowerCase(name);
  gfxInitDefault();
  aptInit();
  romfsInit();
  cfguInit();
}

napp::~napp() {
  worker::exit();
  gfxExit();
  aptExit();
  cfguExit();
  romfsExit();
}

bool napp::Running() { return m_exit ? false : aptMainLoop(); }

void napp::ForceKill() { m_exit = false; }
} // namespace nlc