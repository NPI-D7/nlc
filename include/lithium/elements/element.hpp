#pragma once

namespace nlc {
namespace li {
class element {
private:
protected:
public:
  virtual ~element() = 0;
  virtual void OnRender(float sx, float sy, float sw, float sh) = 0;
};
} // namespace li
} // namespace nlc