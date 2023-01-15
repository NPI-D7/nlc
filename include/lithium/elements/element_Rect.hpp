#pragma once

#include <cstdint>
#include <lithium/elements/element.hpp>

namespace nlc {
namespace li {
class el_Rect : public element {
private:
  float m_x, m_y, m_w, m_h = 0.f;
  uint32_t m_corner_tl;
  uint32_t m_corner_tr;
  uint32_t m_corner_bl;
  uint32_t m_corner_br;
public:
  ~el_Rect() override;
  void OnRender(float sx, float sy, float sw, float sh) override;

  el_Rect();
  el_Rect(float x, float y, float w, float h, uint32_t tl, uint32_t tr,
          uint32_t bl, uint32_t br);
  void SetPosition(float x, float y);
  void SetSize(float w, float h);
  uint32_t GetTopLeft();
  uint32_t GetTopRight();
  uint32_t GetBottomLeft();
  uint32_t GetBottomRight();
  void SetColor(uint32_t tl, uint32_t tr, uint32_t bl, uint32_t br);
  float GetX();
  float GetY();
  float GetW();
  float GetH();
};
} // namespace li
} // namespace nlc