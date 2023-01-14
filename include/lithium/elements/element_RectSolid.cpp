#include <lithium/elements/element_RectSolid.hpp>

#include <nr/nr.hpp>
#include <nr2/nr2.hpp>
#include <nuseful/nuseful.hpp>

namespace nlc {
namespace li {
el_RectSolid::~el_RectSolid() {
  // Nothing
}

void el_RectSolid::OnRender(float sx, float sy, float sw, float sh) {
  nr2::DrawRectSolid(sx + sw * m_x, sy + sh * m_y, m_w, m_h, m_color);
}

el_RectSolid::el_RectSolid() { m_color = nlc::color_storage::Get(""); }

el_RectSolid::el_RectSolid(float x, float y, float w, float h, uint32_t color) {
  m_color = color;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
}

void el_RectSolid::SetPosition(float x, float y) {
  m_x = x;
  m_y = y;
}

void el_RectSolid::SetSize(float w, float h) {
  m_w = w;
  m_h = h;
}

uint32_t el_RectSolid::GetColor() { return m_color; }

void el_RectSolid::SetColor(uint32_t color) { m_color = color; }

float el_RectSolid::GetX() { return m_x; }

float el_RectSolid::GetY() { return m_y; }

float el_RectSolid::GetW() { return m_w; }

float el_RectSolid::GetH() { return m_h; }
} // namespace li
} // namespace nlc