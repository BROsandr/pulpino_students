#include "kuznechik.h"

void      kuznechik_cipher      ( unsigned int data_in [4] ){
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

void      kuznechik_get_ciphered( unsigned int data_out[4] ){
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
