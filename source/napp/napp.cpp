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
  if (isNdsp)
    ndspExit();
  romfsExit();
  gfxExit();
  aptExit();
  worker::exit();
  cfguExit();
}

bool napp::Running() {
  if (!aptMainLoop())
    return false;

  return !m_exit;
}

void napp::ForceKill() { m_exit = true; }

std::string napp::GetSysLangKey() {
  u8 language = 1;
  CFGU_GetSystemLanguage(&language);

  switch (language) {
  case 0:
    return "jp"; // Japanese
    break;

  case 1:
    return "en"; // English
    break;

  case 2:
    return "fr"; // French
    break;

  case 3:
    return "de"; // German
    break;

  case 4:
    return "it"; // Italian
    break;

  case 5:
    return "es"; // Spanish
    break;

  case 6:
    return "zh-CN"; // Chinese (Simplified)
    break;

  case 7:
    return "ko"; // Korean
    break;

  case 8:
    return "nl"; // Dutch
    break;

  case 9:
    return "pt"; // Portuguese
    break;

  case 10:
    return "ru"; // Russian
    break;

  case 11:
    return "zh-TW"; // Chinese (Traditional)
    break;

  default:
    return "en"; // Fall back to English if missing
    break;
  }
  return "en";
}
void napp::InitNdsp() {
  Result res = ndspInit();
  if (R_SUCCEEDED(res)) {
    isNdsp = true;
  }
}
} // namespace nlc