// Element Class file
#include "element.h"

void Element::Init( int x_, int y_, bool alive_) {
  x = x_;
  y = y_;
  alive = alive_;
  will_live = false;
}

void Element::becomes_alive() {
  will_live = true;
}

void Element::dies() {
  will_live = false;
}

void Element::stays_alive() {
  will_live = true;
}
