#include "vga.h"

void      vga_set_pixel      ( unsigned int addr_x, unsigned int addr_y, unsigned int color ){
  VGA_ADDR_X = addr_x;
  VGA_ADDR_Y = addr_y;
  VGA_COLOR  = color;
  VGA_WE     = 1;
}

void      vga_draw_rect      ( unsigned int x, unsigned int y, unsigned int width, unsigned int height ){
  for( int i = x; i < x + width; ++i ) {
    for( int j = y; j < y + height; ++j ) {
      vga_set_pixel(i, j, 1);
    }
  }
}