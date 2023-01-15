#pragma once

#include <cstdint>
#include <lithium/elements/element.hpp>

namespace nlc {
namespace li {
class el_RectSolid : public element {
private:
  float m_x, m_y, m_w, m_h = 0.f;
  uint32_t m_color;
public:
  ~el_RectSolid() override;
  void OnRender(float sx, float sy, float sw, float sh) override;

  el_RectSolid();
  el_RectSolid(float x, float y, float w, float h, uint32_t color);
  void SetPosition(float x, float y);
  void SetSize(float w, float h);
  uint32_t GetColor();
  void SetColor(uint32_t color);
  float GetX();
  float GetY();
  float GetW();
  float GetH();
};
} // namespace li
} // namespace nlc