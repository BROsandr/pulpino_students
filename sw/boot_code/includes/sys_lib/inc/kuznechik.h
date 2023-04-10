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

inline void      kuznechik_cipher      ( unsigned int data_in [4] ){
  unsigned int busy = 1;

  do {
    busy = KUZNECHIK_BUSY;
  } while( busy );

  KUZNECHIK_DATA_IN_0 = data_in[0];
  KUZNECHIK_DATA_IN_1 = data_in[1];
  KUZNECHIK_DATA_IN_2 = data_in[2];
  KUZNECHIK_DATA_IN_3 = data_in[3];

  KUZNECHIK_REQ = 1;
}

inline void      kuznechik_get_ciphered( unsigned int data_out[4] ){
  unsigned int valid = 0;

  do {
    valid = KUZNECHIK_VALID;
  } while( !valid );

  data_out[0] = KUZNECHIK_DATA_OUT_0;
  data_out[1] = KUZNECHIK_DATA_OUT_1;
  data_out[2] = KUZNECHIK_DATA_OUT_2;
  data_out[3] = KUZNECHIK_DATA_OUT_3;

  KUZNECHIK_ACK = 1;
}

#endif // _KUZNECHIK_H_
