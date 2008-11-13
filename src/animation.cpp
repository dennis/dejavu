#include "animation.h"
#include "game.h"
#include "hero.h"

void Animation::init_lua(LuaVM& lua) {
  using namespace luabind;
  module(lua)
  [
    class_<Animation>("Animation")
      .def(constructor<>())
      .def("load", &Animation::load)
  ];
}

Animation::Animation() {
  std::cout << this << " Animation()" << std::endl;
}

Animation::~Animation() {
  std::cout << this << " ~Animation()" << std::endl;
}

AnimationView* Animation::getView() {
  return new AnimationView(this);
}

void Animation::load(const std::string filename, int height, int width) {
  std::cout << this << " Animation::load(" << filename << ")" 
    << std::endl;
  std::wstring filenamew(filename.begin(), filename.end());
  Gosu::imagesFromTiledBitmap(GameWindow::game->graphics(), filenamew, 
    height, width, false, container);
}

void Animation::push_back(boost::shared_ptr<Gosu::Image> image) {
  container.push_back(image);
}
// ex: ts=2 sw=2 et sr
