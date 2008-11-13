#include "common.h"
#include "animation.h"
#include "hero.h"
#include "luavm.h"

void Hero::init_lua(LuaVM& lua) {
  luabind::module(lua) [
    luabind::class_<Hero>("Hero")
      .def_readwrite("xpos", &Hero::xpos)
      .def_readwrite("ypos", &Hero::ypos)
      .def("show", &Hero::show)
  ];
}

Hero::Hero(Gosu::Graphics& graphics) : current(nullptr) {
  std::wstring filename;

  xpos = ypos = 0;
}

void Hero::draw() {
  if(current) {
    boost::shared_ptr<Gosu::Image> image = current->getImage(Gosu::milliseconds()/100%current->size());
    image->draw(xpos, ypos, 0);
  }
}

void Hero::show(Animation& a) {
  std::cout << "show anim! " << &a << std::endl;

  if( current ) 
    delete current;
  current = a.getView();
}

// ex: ts=2 sw=2 et sr
