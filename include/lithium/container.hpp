#pragma once

#include <lithium/elements/elements.hpp>
#include <memory>
#include <vector>

namespace nlc::li {
class container {
private:
  float m_x, m_y, m_w, m_h;
  std::vector<std::unique_ptr<nlc::li::element>> elements;

public:
  container();
};
} // namespace nlc::li