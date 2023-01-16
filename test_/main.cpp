#include <lithium/lithium.hpp>
#include <nlc.hpp>

int main() {
  nlc::napp app("The App");
  nlc::nr::Init();
  nlc::nr2::AddFont("romfs:/roboto_regular.bcfnt", "rr");
  nlc::image imgl;
  imgl.LoadFile("romfs:/TCSL80N.png");
  nlc::color_storage::Add(nlc::color_t("#056423"), "coll");
  nlc::color_storage::Add(nlc::color_t("#ffffff"), "white");

  nlc::li::container container(0, 0, 400, 240);

  nlc::li::el_Button btn(10, 10, 100, 30, "BTN");
  btn.SetTextColor(nlc::color_storage::Get("white"));
  btn.SetSelected(true);
  btn.SetSelColor(nlc::color_storage::Get("coll"));
  btn.SetFont("rr");

  while (app.Running()) {
    nlc::nr::DrawBeg();
    nlc::nr2::DrawOnScreen(0);
    nlc::li::el_RectSolid rect(0, 0, 100, 200, nlc::color_storage::Get("coll"));
    // container.AddElement(rect);
    container.AddElement(btn);
    nlc::nr2::DrawImage(0, 0, imgl);
    nlc::nr2::DrawText(0, 0, 1, nlc::color_t().GetRGBA(), "sdmc:/3ds/Bcstm", 0,
                       0, "sans");
    nlc::nr2::DrawText(0, 30, 1, nlc::color_t().GetRGBA(),
                       nlc::fsys::GetParentPath("sdmc:/3ds/Bcstm", "sdmc:/"), 0,
                       0, "sans");
    nlc::nr2::DrawOnScreen(1);
    nlc::nr2::DrawImage(-40, 0, imgl);
    container.Render();
    nlc::nr::DrawEnd();
  }
  nlc::nr2::UnloadFonts();
  nlc::nr::Exit();
}