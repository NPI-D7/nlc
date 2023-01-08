#include <ctime>
#include <fstream>
#include <nlc.hpp>

static const char *const NPI_Logo = R"text(  
           _   _ ____ ___      ____ _____ 
          | \ | |  _ \_ _|      |  _ \___ |
          |  \| | |_) | |_____| | | | / / 
          | |\  |  __/| |_____| |_| |/ /  
          |_| \_|_|  |___|    |____//_/                                
)text";

std::string to_print = "";
std::string to_inject = "Npi-D7\n\n";

bool is_start = true;
static void Test() {
  int ix = 0;
  to_inject += "Time: " + nlc::ntime::GetTimeStr() + "\n";
  to_inject +=
      "Now Loading "
      "System...\n----------------------------------------------------";
  to_inject += NPI_Logo;
  nlc::worker::sleep(10000);
  while (true) {
    if (ix >= (int)to_inject.length())
      break;
    to_print.push_back(to_inject.at(ix));

    ix++;
    nlc::worker::sleep(20);
  }
  nlc::worker::sleep(1000);
  is_start = false;
}

int main() {
  nlc::napp app("The App");
  nlc::nr::Init();
  nlc::nr2::AddFont("romfs:/roboto_regular.bcfnt", "rr");
  nlc::worker::push(Test, "stringbuilder");
  nlc::image imgl;
  imgl.LoadFile("romfs:/TCSL80N.png");

  while (app.Running()) {
    nlc::nr::DrawBeg();
    nlc::nr2::DrawOnScreen(0);
    nlc::nr2::DrawRect(0, 0, 400, 240, nlc::color_t("#60CCCC"),
                       nlc::color_t("#60CCCC"), nlc::color_t("#429A9F"),
                       nlc::color_t("#429A9F"));
    nlc::nr2::DrawImage(0, 0, imgl);
    nlc::nr2::DrawText(0, 0, 1, nlc::color_t().GetRGBA(), "sdmc:/3ds/Bcstm", 0,
                       0, "sans");
    nlc::nr2::DrawText(0, 30, 1, nlc::color_t().GetRGBA(),
                       nlc::fsys::GetParentPath("sdmc:/3ds/Bcstm", "sdmc:/"), 0,
                       0, "sans");
    if (is_start) {
      nlc::nr2::DrawRectSolid(0, 0, 400, 240, nlc::color_t("#000000"));
      nlc::nr2::DrawText(0, 0, 0.7, nlc::color_t("#ffffff").GetRGBA(), to_print,
                         0, 0, "");
    }

    nlc::nr2::DrawOnScreen(1);
    nlc::nr2::DrawImage(-40, 0, imgl);

    nlc::nr::DrawEnd();
  }
  nlc::nr2::UnloadFonts();
  nlc::nr::Exit();
}