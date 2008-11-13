#ifndef LUAVM_H__
#define LUAVM_H__

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <stdexcept>
#include <sstream>

class LuaVM {
private:
  LuaVM(const LuaVM&) {
    // We don't allow this
  }
public:
  lua_State*  state;

  LuaVM() : state(lua_open()) {
    luaopen_base(state);
    luaopen_table(state);
    luaopen_io(state);
    luaopen_string(state);
    luaopen_math(state);
    luabind::open(state);
  }

  ~LuaVM() {
    lua_close(state);
  }

  operator lua_State*() {
    return state;
  }

  void load(std::string filename) {
    if(luaL_loadfile(state, filename.c_str())) {
      std::stringstream msg;
      msg << "Can't load lua script: " << filename;
      throw std::runtime_error(msg.str());
    }
    if(lua_pcall(state, 0, 0, 0)) {
      std::stringstream msg;
      msg << "Can't parse lua script '" << filename << "': " << 
        lua_tostring(state, -1);
      throw std::runtime_error(msg.str());
    }
  }

  int get_global_number(std::string name) {
    lua_getglobal(state, name.c_str());
    if(!lua_isnumber(state, -1)) {
      std::stringstream msg;
      msg << "'" << name << "' should be a number ";
      throw std::runtime_error(msg.str());
    }

    return (int)lua_tonumber(state, -1);
  }

  std::wstring get_global_string(std::string name) {
    lua_getglobal(state, name.c_str());
    if(!lua_isstring(state, -1)) {
      std::stringstream msg;
      msg << "'" << name << "' should be a string ";
      throw std::runtime_error(msg.str());
    }

    // convert string to wstring 
    std::string str(lua_tostring(state, -1));
    std::wstring wstr(str.begin(),str.end());
    return wstr;
  }

  template<typename T>
  void globals(std::string name, T& t) {
    luabind::globals(state)[name.c_str()] = &t;
  }
};

// ex: ts=2 sw=2 et sr
#endif
