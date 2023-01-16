#pragma once

#include <cstdint>
#include <lithium/elements/element.hpp>
#include <string>

namespace nlc {
namespace li {
class el_Button : public element {
private:
  float m_x, m_y, m_w, m_h = 0.f;
  uint32_t m_color;
  uint32_t m_border_col;
  uint32_t m_selcolor;
  uint32_t textcolor;
  std::string text;
  std::string m_fontreg;
  float m_textsize = 0.7f;
  bool isselected = false;
  bool hasborder = false;
  bool isFilled = false;
  float m_border_size = 2.f;

public:
  ~el_Button() override;
  void OnRender(float sx, float sy, float sw, float sh) override;

  el_Button();
  el_Button(float x, float y, float w, float h, std::string txt);
  void SetPosition(float x, float y);
  void SetSize(float w, float h);
  uint32_t GetColor();
  uint32_t GetBorderColor();
  void SetBorderColor(uint32_t color);
  void SetColor(uint32_t color);
  float GetX();
  float GetY();
  float GetW();
  float GetH();
  std::string GetText();
  void SetText(std::string txt);
  bool IsPressed(float px, float py);
  void SetSelected(bool sel);
  bool IsSelected();
  void SetBorderActive(bool border);
  bool GetBorderActive();
  float GetBoarderSize();
  void SetBorderSize(float border_size);
  void SetFilled(bool filled);
  bool IsFilled();
  uint32_t GetSelColor();
  void SetSelColor(uint32_t sc);
  void SetFont(std::string reg);
  float GetTextSize();
  void SetTextSize(float size);
  uint32_t GetTextColor();
  void SetTextColor(uint32_t color);
};
} // namespace li
} // namespace nlc