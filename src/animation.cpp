#include <cassert>
#include <iostream>

#include "animation.h"
#include "game.h"
#include "hero.h"

void Animation::init_lua(LuaVM& lua) {
  using namespace luabind;
  module(lua)
  [
    class_<Animation>("Animation")
      .def(constructor<>())
      .def("load",  &Animation::load)
      .def("clear", &Animation::clear)
      .def("get_fps", &Animation::get_fps)
      .def("set_fps", &Animation::set_fps)
  ];
}

Animation::Animation() : views(0), fps(10) {
  std::cout << this << " Animation()" << std::endl;
}

Animation::~Animation() {
  std::cout << this << " ~Animation()" << std::endl;
  assert(views == 0 && " ERROR This Animation still got active views to it!");
}

boost::shared_ptr<AnimationView> Animation::getView() {
  return boost::shared_ptr<AnimationView>(new AnimationView(this));
}

void Animation::clear() {
  std::cout << this << " Animation::clear()" << std::endl;
  container.clear();
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
