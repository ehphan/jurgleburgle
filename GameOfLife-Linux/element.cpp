// Element Class file
#include "element.h"

void Element::Init( int x_, int y_, bool alive_) {
  x = x_;
  y = y_;
  alive = alive_;
}

enum ElResult {
  WillLive,
  WillDie,
  WillNotChange
};
