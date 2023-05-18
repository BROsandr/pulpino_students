#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <stdint.h>

#include "pulpino.h"

#define MOUSE_REG_X_POS                     ( MOUSE_BASE_ADDR + 0x00 )
#define MOUSE_REG_Y_POS                     ( MOUSE_BASE_ADDR + 0x04 )
#define MOUSE_REG_ACK                       ( MOUSE_BASE_ADDR + 0x08 )
#define MOUSE_REG_BUTTON                    ( MOUSE_BASE_ADDR + 0x0C )
#define MOUSE_REG_RST                       ( MOUSE_BASE_ADDR + 0x10 )

#define MOUSE_X_POS                      REG( MOUSE_REG_X_POS        )
#define MOUSE_Y_POS                      REG( MOUSE_REG_Y_POS        )
#define MOUSE_ACK                        REG( MOUSE_REG_ACK          )
#define MOUSE_BUTTON                     REG( MOUSE_REG_BUTTON       )
#define MOUSE_RST                        REG( MOUSE_REG_RST          )

void         mouse_init();
   
void         mouse_reset();

#endif // _MOUSE_H_
