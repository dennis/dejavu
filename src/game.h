#ifndef GAME_H__
#define GAME_H__

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <boost/scoped_ptr.hpp>

#include "hero.h"
#include "textfield.h"

class LuaVM;

class GameWindow : public Gosu::Window {
private:
  boost::scoped_ptr<Gosu::Image> background_image;
  boost::scoped_ptr<Gosu::Font> font;
  boost::scoped_ptr<TextField>  console_input;

  bool      show_console;

protected:
  LuaVM&    lua;
  Hero      hero;

public:
  static GameWindow* game;

  static void init_lua(LuaVM&);

  GameWindow(LuaVM&);
  void update();
  void draw();

  void toggle_console();
  void console(bool);

  // callable from lua
  void load_background(const std::string);
  void out(const std::string);
  void buttonDown(Gosu::Button);
};

#endif
// ex: ts=2 sw=2 et sr
