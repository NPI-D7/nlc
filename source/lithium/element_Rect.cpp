#include <lithium/elements/element_Rect.hpp>

#include <nr/nr.hpp>
#include <nr2/nr2.hpp>
#include <nuseful/nuseful.hpp>

namespace nlc {
namespace li {

el_Rect::~el_Rect() {
  // Nothing
}

void el_Rect::OnRender(float sx, float sy, float sw, float sh) {
  nr2::DrawRect(sx + sw * m_x, sy + sh * m_y, sx + sw * m_x + m_w,
                sy + sh * m_y + m_h, m_corner_tl, m_corner_tr, m_corner_bl,
                m_corner_br);
}

el_Rect::el_Rect() {
  m_corner_bl = nlc::color_storage::Get("");
  m_corner_br = nlc::color_storage::Get("");
  m_corner_tl = nlc::color_storage::Get("");
  m_corner_tr = nlc::color_storage::Get("");
}

el_Rect::el_Rect(float x, float y, float w, float h, uint32_t tl, uint32_t tr,
                 uint32_t bl, uint32_t br) {
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_corner_bl = bl;
  m_corner_br = br;
  m_corner_tl = tl;
  m_corner_tr = tr;
}

void el_Rect::SetPosition(float x, float y) {
  m_x = x;
  m_y = y;
}

void el_Rect::SetSize(float w, float h) {
  m_w = w;
  m_h = h;
}

uint32_t el_Rect::GetTopLeft() { return m_corner_tl; }

uint32_t el_Rect::GetTopRight() { return m_corner_tr; }

uint32_t el_Rect::GetBottomLeft() { return m_corner_bl; }

uint32_t el_Rect::GetBottomRight() { return m_corner_br; }

void el_Rect::SetColor(uint32_t tl, uint32_t tr, uint32_t bl, uint32_t br) {
  m_corner_bl = bl;
  m_corner_br = br;
  m_corner_tl = tl;
  m_corner_tr = tr;
}

float el_Rect::GetX() { return m_x; }

float el_Rect::GetY() { return m_y; }

float el_Rect::GetW() { return m_w; }

float el_Rect::GetH() { return m_h; }
} // namespace li
} // namespace nlc