#include <lithium/elements/element_Button.hpp>
#include <nr2/nr2.hpp>

#define fp(x, y, z) (x + y * z)
#define fp2(x, y, z, w) (x + y * z + w)
#define by2(x) (x * 2)

namespace nlc {
namespace li {
el_Button::~el_Button() {
  // Nothing
}

void el_Button::OnRender(float sx, float sy, float sw, float sh) {
  if (hasborder) {
    nlc::nr2::DrawRectSolid(
        fp(sx, sw, m_x) - m_border_size, fp(sy, sh, m_y) - m_border_size,
        fp2(sx, sw, m_x, m_w) + by2(m_border_size),
        fp2(sy, sh, m_y, m_h) + by2(m_border_size), m_border_col);
  }
  if (isFilled) {
    nlc::nr2::DrawRectSolid(fp(sx, sw, m_x), fp(sy, sh, m_y),
                            fp2(sx, sw, m_x, m_w), fp2(sy, sh, m_y, m_h),
                            m_color);
  }
  if (isselected) {
    nlc::nr2::DrawRectSolid(fp(sx, sw, m_x), fp(sy, sh, m_y),
                            fp2(sx, sw, m_x, m_w), fp2(sy, sh, m_y, m_h),
                            m_selcolor);
  }
  nr2::DrawTextCentered(fp(sx, sw, m_x), fp(sy, sh, m_y), m_textsize, textcolor,
                        text, fp2(sx, sw, m_x, m_w), fp2(sy, sh, m_y, m_h),
                        m_fontreg);
}

el_Button::el_Button() {
  m_x = 0;
  m_y = 0;
  m_w = 0;
  m_h = 0;
  m_color = 0x00000000;
  textcolor = 0x00000000;
  m_border_col = 0x00000000;
  m_selcolor = 0x00000000;
  text = "";
}

el_Button::el_Button(float x, float y, float w, float h, std::string txt) {
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  text = txt;
}

void el_Button::SetPosition(float x, float y) {
  m_x = x;
  m_y = y;
}

void el_Button::SetSize(float w, float h) {
  m_w = w;
  m_h = h;
}

uint32_t el_Button::GetColor() { return m_color; }

uint32_t el_Button::GetBorderColor() { return m_border_col; }

void el_Button::SetBorderColor(uint32_t color) { m_border_col = color; }

void el_Button::SetColor(uint32_t color) { m_color = color; }

float el_Button::GetX() { return m_x; }

float el_Button::GetY() { return m_y; }

float el_Button::GetW() { return m_w; }

float el_Button::GetH() { return m_h; }

std::string el_Button::GetText() { return text; }

void el_Button::SetText(std::string txt) { text = txt; }

bool el_Button::IsPressed(float px, float py) {
  if (px >= m_x && px <= (m_x + m_w) && py >= m_y && py <= (m_y + m_h))
    return true;
  else
    return false;
}

void el_Button::SetSelected(bool sel) { isselected = sel; }

bool el_Button::IsSelected() { return isselected; }

void el_Button::SetBorderActive(bool border) { hasborder = border; }

bool el_Button::GetBorderActive() { return hasborder; }

float el_Button::GetBoarderSize() { return m_border_size; }

void el_Button::SetBorderSize(float border_size) {
  m_border_size = border_size;
}

void el_Button::SetFilled(bool filled) { isFilled = filled; }

bool el_Button::IsFilled() { return isFilled; }

uint32_t el_Button::GetSelColor() { return m_selcolor; }

void el_Button::SetSelColor(uint32_t sc) { m_selcolor = sc; }

void el_Button::SetFont(std::string reg) { m_fontreg = reg; }

float el_Button::GetTextSize() { return m_textsize; }

void el_Button::SetTextSize(float size) { m_textsize = size; }

uint32_t el_Button::GetTextColor() { return textcolor; }

void el_Button::SetTextColor(uint32_t color) { textcolor = color; }
} // namespace li
} // namespace nlc