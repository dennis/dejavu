#include "animation.h"
#include "game.h"

GameWindow* GameWindow::game = 0L;

void GameWindow::init_lua(LuaVM& lua) {
  using namespace luabind;
  module(lua) 
  [
    class_<GameWindow>("GameWindow")
          .def("load_background", &GameWindow::load_background)
          .def("out", &GameWindow::out)
  ];
}

GameWindow::GameWindow(LuaVM& lvm) : Window(640, 480, false), lua(lvm), hero(graphics()) {
  if(!GameWindow::game)
    GameWindow::game = this;

  setCaption(lua.get_global_string("caption").c_str());
  Hero::init_lua(lua);
  Animation::init_lua(lua);
  lua.globals("hero", hero);
}

void GameWindow::update() {
  /*
  if(input().down(Gosu::kbLeft))
    hero.walkLeft();
  else if(input().down(Gosu::kbRight))
    hero.walkRight();
  else
    hero.stop();
  */
  hero.update();
}

void GameWindow::draw() {
  if(background_image.get())
    background_image->draw(0, 0, 0);
  hero.draw();
}


void GameWindow::load_background(const std::string str) { // Callable from lua
  // convert string to wstring 
  std::wstring wstr(str.begin(),str.end());
  std::wstring filename = get_data_dirw() + wstr;
  background_image.reset(new Gosu::Image(graphics(), filename));
}

void GameWindow::out(const std::string) {
}
 
void GameWindow::buttonDown(Gosu::Button btn) {
  if(btn == Gosu::kbEscape)
    close();
}
// ex: ts=2 sw=2 et sr
