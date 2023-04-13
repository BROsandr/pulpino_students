#ifndef _KUZNECHIK_H_
#define _KUZNECHIK_H_

#include <stdint.h>

#include "pulpino.h"

#define KUZNECHIK_REG_RST                       ( KUZNECHIK_BASE_ADDR + 0x00 )
#define KUZNECHIK_REG_REQ                       ( KUZNECHIK_BASE_ADDR + 0x04 )
#define KUZNECHIK_REG_ACK                       ( KUZNECHIK_BASE_ADDR + 0x08 )
#define KUZNECHIK_REG_VALID                     ( KUZNECHIK_BASE_ADDR + 0x0C )
#define KUZNECHIK_REG_BUSY                      ( KUZNECHIK_BASE_ADDR + 0x10 )
#define KUZNECHIK_REG_DATA_IN_0                 ( KUZNECHIK_BASE_ADDR + 0x14 )
#define KUZNECHIK_REG_DATA_IN_1                 ( KUZNECHIK_BASE_ADDR + 0x18 )
#define KUZNECHIK_REG_DATA_IN_2                 ( KUZNECHIK_BASE_ADDR + 0x1c )
#define KUZNECHIK_REG_DATA_IN_3                 ( KUZNECHIK_BASE_ADDR + 0x20 )
#define KUZNECHIK_REG_DATA_OUT_0                ( KUZNECHIK_BASE_ADDR + 0x24 )
#define KUZNECHIK_REG_DATA_OUT_1                ( KUZNECHIK_BASE_ADDR + 0x28 )
#define KUZNECHIK_REG_DATA_OUT_2                ( KUZNECHIK_BASE_ADDR + 0x2c )
#define KUZNECHIK_REG_DATA_OUT_3                ( KUZNECHIK_BASE_ADDR + 0x30 )

#define KUZNECHIK_RST                        REG( KUZNECHIK_REG_RST          )
#define KUZNECHIK_REQ                        REG( KUZNECHIK_REG_REQ          )
#define KUZNECHIK_ACK                        REG( KUZNECHIK_REG_ACK          )
#define KUZNECHIK_VALID                      REG( KUZNECHIK_REG_VALID        )
#define KUZNECHIK_BUSY                       REG( KUZNECHIK_REG_BUSY         )
#define KUZNECHIK_DATA_IN_0                  REG( KUZNECHIK_REG_DATA_IN_0    )
#define KUZNECHIK_DATA_IN_1                  REG( KUZNECHIK_REG_DATA_IN_1    )
#define KUZNECHIK_DATA_IN_2                  REG( KUZNECHIK_REG_DATA_IN_2    )
#define KUZNECHIK_DATA_IN_3                  REG( KUZNECHIK_REG_DATA_IN_3    )
#define KUZNECHIK_DATA_OUT_0                 REG( KUZNECHIK_REG_DATA_OUT_0   )
#define KUZNECHIK_DATA_OUT_1                 REG( KUZNECHIK_REG_DATA_OUT_1   )
#define KUZNECHIK_DATA_OUT_2                 REG( KUZNECHIK_REG_DATA_OUT_2   )
#define KUZNECHIK_DATA_OUT_3                 REG( KUZNECHIK_REG_DATA_OUT_3   )

// inline void      kuznechik_set( uintptr_t reg_addr, unsigned int data ){
//   REG(reg_addr) = data;
// }

// inline uintptr_t kuznechik_get( uintptr_t reg_addr ){
//   return REG(reg_addr);
// }

void      kuznechik_get_ciphered( unsigned int data_out[4] );
void      kuznechik_cipher      ( unsigned int data_in [4] );

#endif // _KUZNECHIK_H_
