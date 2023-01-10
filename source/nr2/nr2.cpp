#include <citro2d.h>
#include <citro3d.h>
#include <map>
#include <nr2/nr2.hpp>
#include <nuseful/stringtools.hpp>
#include <vector>

extern C3D_RenderTarget *targets[3];

extern C2D_TextBuf TextBuf;
extern C2D_Font Font;
bool currentScreen;

struct Font__ {
  std::string name;
  C2D_Font fnt;
  ;
};

std::vector<Font__> font_storage;

C2D_Font GetFromReg(std::string reg) {
  for (auto const &it : font_storage) {
    if (it.name == nlc::st::ToLowerCase(reg))
      return it.fnt;
  }
  return Font;
}

extern C2D_Image *GetImage(int reg);

namespace nlc {
namespace nr2 {
void DrawOnScreen(int screen) {
  C2D_SceneBegin(targets[screen]);
  currentScreen = ((screen == 1) ? false : true);
}
void DrawRect(int x, int y, int w, int h, color_t tl, color_t tr, color_t bl,
              color_t br) {
  C2D_DrawRectangle(x, y, 0.5, w, h, tl.GetRGBA(), tr.GetRGBA(), bl.GetRGBA(),
                    br.GetRGBA());
}
void DrawRectSolid(int x, int y, int w, int h, color_t color) {
  C2D_DrawRectSolid(x, y, 0.5, w, h, color.GetRGBA());
}
void DrawCircle(int x, int y, float r, color_t tl, color_t tr, color_t bl,
                color_t br) {
  C2D_DrawCircle(x, y, 0.5, r, tl.GetRGBA(), tr.GetRGBA(), bl.GetRGBA(),
                 br.GetRGBA());
}
void DrawCircleSolid(int x, int y, float r, color_t color) {
  C2D_DrawCircleSolid(x, y, 0.5, r, color.GetRGBA());
}
void DrawEllipse(int x, int y, int w, int h, color_t tl, color_t tr, color_t bl,
                 color_t br) {
  C2D_DrawEllipse(x, y, 0.5, w, h, tl.GetRGBA(), tr.GetRGBA(), bl.GetRGBA(),
                  br.GetRGBA());
}
void DrawEllipseSolid(int x, int y, int w, int h, color_t color) {
  C2D_DrawEllipseSolid(x, y, 0.5, w, h, color.GetRGBA());
}
void DrawTrangle(float x0, float y0, color_t cl0, float x1, float y1,
                 color_t cl1, float x2, float y2, color_t cl2, float d) {
  C2D_DrawTriangle(x0, y0, cl0.GetRGBA(), x1, y1, cl1.GetRGBA(), x2, y2,
                   cl2.GetRGBA(), d);
}
void DrawLine(float x0, float y0, color_t cl0, float x1, float y1, color_t cl1,
              float t, float d) {
  C2D_DrawLine(x0, y0, cl0.GetRGBA(), x1, y1, cl1.GetRGBA(), t, d);
}

void DrawTextCentered(float x, float y, float size, u32 color, std::string Text,
                      int maxWidth, int maxHeight, std::string fontreg) {
  float lineHeight, widthScale = 0;

  // Check for the lineHeight.
  lineHeight = GetTextHeight(size, " ", fontreg);

  int line = 0;
  while (Text.find('\n') != Text.npos) {
    if (maxWidth == 0) {
      // Do the widthScale.
      widthScale = GetTextWidth(size, Text.substr(0, Text.find('\n')), fontreg);
    } else {
      // Do the widthScale 2.
      widthScale = std::min(
          (float)maxWidth,
          GetTextWidth(size, Text.substr(0, Text.find('\n')), fontreg));
    }
  }
  DrawText((currentScreen ? 200 : 160) + x - (widthScale / 2),
           y + (lineHeight * line), size, color,
           Text.substr(0, Text.find('\n')), maxWidth, maxHeight, fontreg);
  Text = Text.substr(Text.find('\n') + 1);
  line++;

  if (maxWidth == 0) {
    // Do the next WidthScale.
    widthScale = GetTextWidth(size, Text.substr(0, Text.find('\n')), fontreg);
  } else {
    // And again.
    widthScale =
        std::min((float)maxWidth,
                 GetTextWidth(size, Text.substr(0, Text.find('\n')), fontreg));
  }
  DrawText((currentScreen ? 200 : 160) + x - (widthScale / 2),
           y + (lineHeight * line), size, color,
           Text.substr(0, Text.find('\n')), maxWidth, maxHeight, fontreg);
}

// Draw String or Text.
void DrawText(float x, float y, float size, u32 color, std::string Text,
              int maxWidth, int maxHeight, std::string fontreg) {
  C2D_Text c2d_text;

  C2D_TextFontParse(&c2d_text, GetFromReg(fontreg), TextBuf, Text.c_str());

  C2D_TextOptimize(&c2d_text);

  float heightScale;
  if (maxHeight == 0) {
    heightScale = size;
  } else {
    heightScale =
        std::min(size, size * (maxHeight / GetTextHeight(size, Text, fontreg)));
  }

  if (maxWidth == 0) {
    C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, size, heightScale,
                 color);
  } else {
    C2D_DrawText(
        &c2d_text, C2D_WithColor, x, y, 0.5f,
        std::min(size, size * (maxWidth / GetTextWidth(size, Text, fontreg))),
        heightScale, color);
  }
}
void DrawTextRight(float x, float y, float size, u32 color, std::string Text,
                   int maxWidth, int maxHeight, std::string fontreg) {
  DrawText(x - GetTextWidth(size, Text, fontreg), y, size, color, Text,
           maxWidth, maxHeight, fontreg);
}
// Get String or Text Width.
float GetTextWidth(float size, std::string Text, std::string fontreg) {
  float width = 0;
  GetTextSize(size, &width, NULL, Text, fontreg);
  return width;
}

// Get String or Text Size.
void GetTextSize(float size, float *width, float *height, std::string Text,
                 std::string fontreg) {
  C2D_Text c2d_text;
  C2D_TextFontParse(&c2d_text, GetFromReg(fontreg), TextBuf, Text.c_str());
  C2D_TextGetDimensions(&c2d_text, size, size, width, height);
}

// Get String or Text Height.
float GetTextHeight(float size, std::string Text, std::string fontreg) {
  float height = 0;
  GetTextSize(size, NULL, &height, Text.c_str(), fontreg);
  return height;
}

bool AddFont(const char *Path, std::string regname) {
  Font__ temp;
  temp.fnt = C2D_FontLoad(Path); // Only load if found.
  temp.name = nlc::st::ToLowerCase(regname);
  if (temp.fnt)
    font_storage.push_back(temp);
  return 0;
}
// Unload a Font
bool UnloadFonts() {
  for (auto const &it : font_storage)
    if (it.fnt != nullptr) {
      C2D_FontFree(it.fnt); // Make sure to only unload if not nullptr.
    }
  return 0;
}

void DrawImage(int x, int y, image img, float scalex, float scaley) {
  C2D_DrawImageAt(GetImage(img.GetReg())[0], x, y, 0.5, nullptr, scalex,
                  scaley);
}
} // namespace nr2
} // namespace nlc