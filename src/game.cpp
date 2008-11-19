#include <Gosu/Utility.hpp>
#include <iostream>

#include "animation.h"
#include "game.h"
#include "textfield.h"

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

GameWindow::GameWindow(LuaVM& lvm) : Window(640, 480, false), show_console(false), lua(lvm), hero(graphics()) {
  if(!GameWindow::game)
    GameWindow::game = this;

  setCaption(lua.get_global_string("caption").c_str());
  Hero::init_lua(lua);
  Animation::init_lua(lua);
  lua.globals("hero", hero);

  const int fontsize = 12;
  font.reset(new Gosu::Font(graphics(), Gosu::defaultFontName(), fontsize));
  console_input.reset(new TextField(*this, *font, 0, 480-fontsize-5));
}

void GameWindow::update() {
  hero.update();
}

void GameWindow::draw() {
  if(background_image.get())
    background_image->draw(0, 0, 0);
  if(show_console)
    console_input->draw();
  hero.draw();
}


void GameWindow::load_background(const std::string str) { // Callable from lua
  background_image.reset(new Gosu::Image(graphics(), Gosu::widen(str)));
}

void GameWindow::out(const std::string) {
}

void GameWindow::toggle_console() {
  console(!show_console);
}

void GameWindow::console(bool enabled) {
  if(enabled) {
    input().setTextInput(console_input.get());
    std::cout << "console: enabled" << std::endl;
    show_console = true;
  }
  else {
    input().setTextInput(0);
    std::cout << "console: disabled" << std::endl;
    show_console = false;
  }
}
 

void GameWindow::buttonDown(Gosu::Button btn) {
  if(btn == Gosu::kbEscape) {
    if(input().textInput())
      console(false);
    else
      close();
  }
  else if(btn == Gosu::kbTab) {
    toggle_console();
  }
  else if(btn == Gosu::kbReturn) {
    try {
      // This will throw an runtime_error exception, if there are "invalid" chars, such as æøå
      std::string line = Gosu::narrow(console_input->text());
      std::cout << ">> " << line << std::endl;   
      lua.perform(line);
    }
    catch(std::runtime_error&) {
      std::cerr << "Invalid characters!" << std::endl;
    }
    console_input->setText(L"");
  }
}

// ex: ts=2 sw=2 et sr
