#ifndef HERO_H__
#define HERO_H__

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include "common.h"
#include "animation.h"

class LuaVM;

class Hero {
private:
  AnimationView*        current;

  int xpos, ypos;

public:
  static void init_lua(LuaVM&);

  // c'tor
  Hero(Gosu::Graphics&);

  void update();
  void draw();

  void show(Animation&);
};
#endif
// ex: ts=2 sw=2 et sr
