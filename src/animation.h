#ifndef ANIMATION_H__
#define ANIMATION_H__

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "common.h"
#include "luavm.h"

class AnimationView;
class Animation {
private:
  typedef std::vector<boost::shared_ptr<Gosu::Image> > container_t;
  container_t container;
  friend class AnimationView;

public:
  typedef container_t::value_type value_type;

  static void init_lua(LuaVM&);

  Animation();
  ~Animation();

  // iterators
  typedef container_t::iterator iterator;
  typedef container_t::const_iterator const_iterator;
  iterator begin() { return container.begin(); }
  const_iterator begin() const { return container.begin(); }
  iterator end() { return container.end(); }
  const_iterator end() const { return container.end(); }

  AnimationView* getView();
  void load(const std::string, int, int);
  void push_back(boost::shared_ptr<Gosu::Image>);
};

class AnimationView {
public:
  typedef unsigned int index_type;

  index_type  idx;

private:
  Animation*  anim;

public:
  AnimationView() : idx(0), anim(nullptr) {
  }

  AnimationView(Animation* a) : idx(0), anim(a) {
  }

  Gosu::Image* getImage() {
    return getImage(idx);
  }

  Gosu::Image* getImage(index_type i) {
    assert(anim);
    return anim->container.at(i).get();
  }

  int size() {
    return anim->container.size();
  }
};

/*
template<typename T, typename H>
class View {
private:
  T data;
  H helper;

public:
  View(T t) : data(t) {
  }
  operator Gosu::Image*() const {
    return helper();
  }
};

class ImageGetFunctor {
public:
  Gosu::Image* image;

  ImageGetFunctor(Gosu::Image* i) : image(i) {
  }

  Gosu::Image* operator()() {
    return i;
  }
};

class AnimationGetFunctor {
public:
  typedef unsigned int index_type;
  Animation*  anim;
  index_type idx;

  AnimationGetFunctor(Animation* a) : anim(a), idx(0) {
  }

  Gosu::Image* operator()() {
    return &anim.container.at(0).get();
  }
}

typedef View<Gosu::Image, ImageGetFunctor> ImageView;
typedef View<Animation, AnimationGetFunctor> AnimationView;
*/
#endif
// ex: ts=2 sw=2 et sr