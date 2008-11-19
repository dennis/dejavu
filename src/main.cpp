#include <boost/scoped_ptr.hpp>

#include "luavm.h"
#include "game.h"
#include "common.h"

int main(int /*argc*/, char* /*argv*/[]) {
  LuaVM       lua;

  lua.load(get_data_dir() + "lua/init.lua");
  GameWindow window(lua);
  GameWindow::init_lua(lua);
  lua.globals("core", window);
  lua.load(get_data_dir() + "lua/default.lua");
  window.show();
}
// ex: ts=2 sw=2 et sr
