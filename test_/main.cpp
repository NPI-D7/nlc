#include <ctime>
#include <fstream>
#include <nlc.hpp>

int main() {
  nlc::napp app("The App");
  nlc::nr::Init();
  nlc::nconfig conf(0);
  conf.Load("sdmc:/config.json");
  conf.Set("color", 20);
  conf.UpdateVersion(0);
  conf.Set("#ff0000", nlc::color_t("#ff0000").GetHex());
  conf.Save();

  while (app.Running()) {
    nlc::nr::DrawBeg();
    nlc::nr2::DrawOnScreen(0);
    nlc::nr2::DrawRectSolid(0, 0, 150, 100, nlc::color_t("#00ff00"));
    nlc::nr2::DrawText(0, 0, 0.7, nlc::color_t("#ffffff").GetRGBA(), "Hello");
    nlc::nr::DrawEnd();
  }
  nlc::nr::Exit();
}