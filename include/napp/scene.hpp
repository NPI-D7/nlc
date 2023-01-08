#pragma once
#include <memory>
#include <stack>

namespace nlc {
class scene {
public:
  static std::stack<std::unique_ptr<scene>> scenes;
  virtual ~scene() {}
  virtual void Logic() = 0;
  virtual void Draw() = 0;
  static void Load(std::unique_ptr<scene> scene);
  static void Back();
  static void doDraw();
  static void doLogic();
  // static void HandleOvl();
};
} // namespace nlc