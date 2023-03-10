#pragma once

#include <algorithm>
#include <lithium/elements/elements.hpp>
#include <memory>
#include <vector>

namespace nlc::li {
class container {
private:
  float m_x, m_y, m_w, m_h;
  std::vector<nlc::li::element *> elements;

public:
  container(float x, float y, float w, float h) {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
  }
  void Render() {
    for (auto const &it : elements) {
      it->OnRender(m_x, m_y, m_w, m_h);
    }
    elements.clear();
  }
  void AddElement(nlc::li::element &elm) { elements.push_back(&elm); }
};
} // namespace nlc::li