#pragma once
#include <nr2/image.hpp>
#include <nuseful/color.hpp>
#include <string>

namespace nlc {
namespace nr2 {
void DrawOnScreen(int screen = 0);
void DrawRect(int x, int y, int w, int h, uint32_t tl, uint32_t tr, uint32_t bl,
              uint32_t br);
void DrawRectSolid(int x, int y, int w, int h, uint32_t color);
void DrawCircle(int x, int y, float r, uint32_t tl, uint32_t tr, uint32_t bl,
                uint32_t br);
void DrawCircleSolid(int x, int y, float r, uint32_t color);
void DrawEllipse(int x, int y, int w, int h, uint32_t tl, uint32_t tr,
                 uint32_t bl, uint32_t br);
void DrawEllipseSolid(int x, int y, int w, int h, uint32_t color);
void DrawTrangle(float x0, float y0, uint32_t cl0, float x1, float y1,
                 uint32_t cl1, float x2, float y2, uint32_t cl2, float d);
void DrawLine(float x0, float y0, uint32_t cl0, float x1, float y1,
              uint32_t cl1, float t, float d);
float GetTextHeight(float size, std::string Text, std::string fontreg = "");
void DrawTextCentered(float x, float y, float size, uint32_t color,
                      std::string Text, int maxWidth = 0, int maxHeight = 0,
                      std::string fontreg = "");
void DrawText(float x, float y, float size, uint32_t color, std::string Text,
              int maxWidth = 0, int maxHeight = 0, std::string fontreg = "");
void DrawTextRight(float x, float y, float size, uint32_t color,
                   std::string Text, int maxWidth = 0, int maxHeight = 0,
                   std::string fontreg = "");
float GetTextWidth(float size, std::string Text, std::string fontreg = "");
void GetTextSize(float size, float *width, float *height, std::string Text,
                 std::string fontreg = "");

bool AddFont(const char *Path = "", std::string regname = "");
bool UnloadFonts();
void DrawImage(int x, int y, image img, float scalex = 1.f, float scaley = 1.f);
} // namespace nr2
} // namespace nlc