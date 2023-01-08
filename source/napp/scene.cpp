#include <napp/scene.hpp>

std::stack<std::unique_ptr<nlc::scene>> nlc::scene::scenes;

namespace nlc {
void scene::Load(std::unique_ptr<scene> scene) {
  scene::scenes.push(std::move(scene));
}

void scene::Back() {
  if (nlc::scene::scenes.size() > 0)
    nlc::scene::scenes.pop();
}

void scene::doDraw() {
  if (!nlc::scene::scenes.empty())
    nlc::scene::scenes.top()->Draw();
}

void scene::doLogic() {
  if (!nlc::scene::scenes.empty())
    nlc::scene::scenes.top()->Logic();
}
} // namespace nlc