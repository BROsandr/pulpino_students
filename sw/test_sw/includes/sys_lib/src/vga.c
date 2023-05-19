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
      vga_set_pixel(i, j, VGA_WHITE);
    }
  }
}

void      vga_clear      ( ){
  for( int i = 0; i < VGA_HEIGHT; ++i ) {
    for( int j = 0; j < VGA_WIDTH; ++j ) {
      vga_set_pixel(i, j, VGA_BLACK);
    }
  }
}

void      vga_init() {
  vga_clear();
}
