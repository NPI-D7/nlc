#include <citro2d.h>
#include <citro3d.h>
#include <map>
#include <nr2/nr2.hpp>

extern C3D_RenderTarget *targets[3];

extern C2D_TextBuf TextBuf;
extern C2D_Font Font;
bool currentScreen;

namespace nlc {
namespace nr2 {
void DrawOnScreen(int screen) {
  C2D_SceneBegin(targets[screen]);
  currentScreen = (screen == 1) ? 0 : 1;
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
                      int maxWidth, int maxHeight, C2D_Font fnt) {
  float lineHeight, widthScale;

  // Check for the lineHeight.
  if (fnt != nullptr) {
    lineHeight = GetTextHeight(size, " ", fnt);
  } else {
    lineHeight = GetTextHeight(size, " ");
  }

  int line = 0;
  while (Text.find('\n') != Text.npos) {
    if (maxWidth == 0) {
      // Do the widthScale.
      if (fnt != nullptr) {
        widthScale = GetTextWidth(size, Text.substr(0, Text.find('\n')), fnt);
      } else {
        widthScale = GetTextWidth(size, Text.substr(0, Text.find('\n')));
      }
    } else {
      // Do the widthScale 2.
      if (fnt != nullptr) {
        widthScale =
            std::min((float)maxWidth,
                     GetTextWidth(size, Text.substr(0, Text.find('\n')), fnt));
      } else {
        widthScale =
            std::min((float)maxWidth,
                     GetTextWidth(size, Text.substr(0, Text.find('\n'))));
      }
    }
    if (fnt != nullptr) {
      DrawText((currentScreen ? 200 : 160) + x - (widthScale / 2),
               y + (lineHeight * line), size, color,
               Text.substr(0, Text.find('\n')), maxWidth, maxHeight, fnt);
    } else {
      DrawText((currentScreen ? 200 : 160) + x - (widthScale / 2),
               y + (lineHeight * line), size, color,
               Text.substr(0, Text.find('\n')), maxWidth, maxHeight);
    }

    Text = Text.substr(Text.find('\n') + 1);
    line++;
  }

  if (maxWidth == 0) {
    // Do the next WidthScale.
    if (fnt != nullptr) {
      widthScale = GetTextWidth(size, Text.substr(0, Text.find('\n')), fnt);
    } else {
      widthScale = GetTextWidth(size, Text.substr(0, Text.find('\n')));
    }
  } else {
    // And again.
    if (fnt != nullptr) {
      widthScale =
          std::min((float)maxWidth,
                   GetTextWidth(size, Text.substr(0, Text.find('\n')), fnt));
    } else {
      widthScale = std::min(
          (float)maxWidth, GetTextWidth(size, Text.substr(0, Text.find('\n'))));
    }
  }
  if (fnt != nullptr) {
    DrawText((currentScreen ? 200 : 160) + x - (widthScale / 2),
             y + (lineHeight * line), size, color,
             Text.substr(0, Text.find('\n')), maxWidth, maxHeight, fnt);
  } else {
    DrawText((currentScreen ? 200 : 160) + x - (widthScale / 2),
             y + (lineHeight * line), size, color,
             Text.substr(0, Text.find('\n')), maxWidth, maxHeight);
  }
}

// Draw String or Text.
void DrawText(float x, float y, float size, u32 color, std::string Text,
              int maxWidth, int maxHeight, C2D_Font fnt) {
  C2D_Text c2d_text;

  if (fnt != nullptr) {
    C2D_TextFontParse(&c2d_text, fnt, TextBuf, Text.c_str());
  } else {
    C2D_TextFontParse(&c2d_text, Font, TextBuf, Text.c_str());
  }

  C2D_TextOptimize(&c2d_text);

  float heightScale;
  if (maxHeight == 0) {
    heightScale = size;
  } else {
    if (fnt != nullptr) {
      heightScale =
          std::min(size, size * (maxHeight / GetTextHeight(size, Text, fnt)));
    } else {
      heightScale =
          std::min(size, size * (maxHeight / GetTextHeight(size, Text)));
    }
  }

  if (maxWidth == 0) {
    C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, size, heightScale,
                 color);
  } else {
    if (fnt != nullptr) {
      C2D_DrawText(
          &c2d_text, C2D_WithColor, x, y, 0.5f,
          std::min(size, size * (maxWidth / GetTextWidth(size, Text, fnt))),
          heightScale, color);
    } else {
      C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f,
                   std::min(size, size * (maxWidth / GetTextWidth(size, Text))),
                   heightScale, color);
    }
  }
}
void DrawTextRight(float x, float y, float size, u32 color, std::string Text,
                   int maxWidth, int maxHeight, C2D_Font fnt) {
  DrawText(x - GetTextWidth(size, Text, fnt), y, size, color, Text, maxWidth,
           maxHeight, fnt);
}
// Get String or Text Width.
float GetTextWidth(float size, std::string Text, C2D_Font fnt) {
  float width = 0;
  if (fnt != nullptr) {
    GetTextSize(size, &width, NULL, Text, fnt);
  } else {
    GetTextSize(size, &width, NULL, Text);
  }
  return width;
}

// Get String or Text Size.
void GetTextSize(float size, float *width, float *height, std::string Text,
                 C2D_Font fnt) {
  C2D_Text c2d_text;
  if (fnt != nullptr) {
    C2D_TextFontParse(&c2d_text, fnt, TextBuf, Text.c_str());
  } else {
    C2D_TextFontParse(&c2d_text, Font, TextBuf, Text.c_str());
  }
  C2D_TextGetDimensions(&c2d_text, size, size, width, height);
}

// Get String or Text Height.
float GetTextHeight(float size, std::string Text, C2D_Font fnt) {
  float height = 0;
  if (fnt != nullptr) {
    GetTextSize(size, NULL, &height, Text.c_str(), fnt);
  } else {
    GetTextSize(size, NULL, &height, Text.c_str());
  }
  return height;
}

bool LoadFont(C2D_Font &fnt, const char *Path) {
  fnt = C2D_FontLoad(Path); // Only load if found.
  return 0;
}

// Unload a Font.s
bool UnloadFont(C2D_Font &fnt) {
  if (fnt != nullptr) {
    C2D_FontFree(fnt); // Make sure to only unload if not nullptr.
  }
  return 0;
}
} // namespace nr2
} // namespace nlc