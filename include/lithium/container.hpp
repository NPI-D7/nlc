#pragma once

#include <lithium/elements/elements.hpp>
#include <algorithm>
#include <memory>
#include <vector>

namespace nlc::li {
class container {
private:
  float m_x, m_y, m_w, m_h;
  std::vector<nlc::li::element*> elements;

public:
  container() {
    m_x = 0;
    m_y = 0;
    m_w = 0;
    m_h = 0;
  }
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
  void AddElement(nlc::li::element& elm) {
    elements.push_back(&elm);
  }
};
} // namespace nlc::li