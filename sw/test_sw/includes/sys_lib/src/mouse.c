#include "mouse.h"

void      mouse_init() {
  MOUSE_RST = 1;
}

void      mouse_reset() { 
  MOUSE_RST = 0;
  MOUSE_RST = 1;
}
