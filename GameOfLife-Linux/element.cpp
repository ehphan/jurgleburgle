// Element Class file
#include "element.h"
#include "stdio.h"

void Element::Init( int x_, int y_, bool alive_) {
  x = x_;
  y = y_;
  alive = alive_;
}

void Element::display_status() {
  printf("Status [%i, %i]: alive? %s\n", x, y, alive ? "true" : "false");
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
