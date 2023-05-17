#ifndef _VGA_H_
#define _VGA_H_

#include <stdint.h>

#include "pulpino.h"

#define VGA_REG_ADDR_X                    ( VGA_BASE_ADDR + 0x00 )
#define VGA_REG_ADDR_Y                    ( VGA_BASE_ADDR + 0x04 )
#define VGA_REG_COLOR                     ( VGA_BASE_ADDR + 0x08 )
#define VGA_REG_WE                        ( VGA_BASE_ADDR + 0x0c )

#define VGA_ADDR_X                     REG( VGA_REG_ADDR_X       )
#define VGA_ADDR_Y                     REG( VGA_REG_ADDR_Y       )
#define VGA_COLOR                      REG( VGA_REG_COLOR        )
#define VGA_WE                         REG( VGA_REG_WE           )

void      vga_set_pixel      ( unsigned int addr_x, unsigned int addr_y, unsigned int color );

void      vga_draw_rect      ( unsigned int x, unsigned int y, unsigned int width, unsigned int height );

#endif // _VGA_H_
