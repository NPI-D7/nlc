#pragma once
#include <cinttypes>
#include <regex>
#include <sstream>
#include <string>

#define RGBA8(r, g, b, a)                                                      \
  ((((r)&0xFF) << 0) | (((g)&0xFF) << 8) | (((b)&0xFF) << 16) |                \
   (((a)&0xFF) << 24))

namespace nlc {
struct color_t {
  color_t() {
    m_r = 1.f;
    m_g = 1.f;
    m_b = 1.f;
    m_a = 1.f;
  }
  color_t(float r, float g, float b, float a = 1.f) {
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
  }

  color_t(std::string color, float a = 1.f) {
    bool skp = false;
    if (color.length() < 7 ||
        std::regex_search(color.substr(1),
                          std::regex("[^0-9A-Fa-f]"))) { // invalid color.
      skp = true;
    }
    if (!skp) {
      int r = std::stoi(color.substr(1, 2), nullptr, 16);
      int g = std::stoi(color.substr(3, 2), nullptr, 16);
      int b = std::stoi(color.substr(5, 2), nullptr, 16);

      m_a = a;
      m_r = (float)((float)r / (float)255);
      m_g = (float)((float)g / (float)255);
      m_b = (float)((float)b / (float)255);
    } else {
      m_a = a;
      m_r = 1;
      m_g = 1;
      m_b = 1;
    }
  }

  uint8_t GetR8() { return m_r * 255; }
  uint8_t GetG8() { return m_g * 255; }
  uint8_t GetB8() { return m_b * 255; }
  uint8_t GetA8() { return m_a * 255; }

  float GetRF() { return m_r; }
  float GetGF() { return m_g; }
  float GetBF() { return m_b; }
  float GetAF() { return m_a; }

  std::string GetHex() {
    std::stringstream ss;
    ss << "#";
    ss << std::hex
       << ((uint32_t)RGBA8((int)(m_r * 255), (int)(m_g * 255), (int)(m_b * 255),
                           (255)));
    return ss.str();
  }

  uint32_t GetRGB888() {
    return (uint32_t)RGBA8((int)(m_r * 255), (int)(m_g * 255), (int)(m_b * 255),
                           (255));
  }
  uint32_t GetRGBA() {
    return (uint32_t)RGBA8((int)(m_r * 255), (int)(m_g * 255), (int)(m_b * 255),
                           (int)(m_a * 255));
  }

  float m_r, m_g, m_b = 0.f;
  float m_a = 1.f;
};
} // namespace nlc