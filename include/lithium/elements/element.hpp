#pragma once

namespace nlc {
namespace li {
class element {
public:
  virtual ~element(){};
  virtual void OnRender(float sx, float sy, float sw, float sh) = 0;
};
} // namespace li
} // namespace nlc