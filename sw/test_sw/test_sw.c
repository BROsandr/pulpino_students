#define __riscv__
#define LED_DELAY 1000000

//#include <spi.h>
#include <gpio.h>
#include <uart.h>
//#include <utils.h>
#include <pulpino.h>
#include <kuznechik.h>

void cipher_and_print( unsigned int data[4] ) {
  kuznechik_cipher( data );
  char kuznechik2me[16];
  kuznechik_get_ciphered( (unsigned int *)kuznechik2me );
  char buff[17];
  for( int i = 0; i < 16; ++i ) {
    buff[15-i] = kuznechik2me[i];
  }
  buff[16] = '\0';
  uart_send( buff, 16 );
}

int main()
{
  uart_set_cfg(0, 325); // 9600 baud UART, no parity (50MHz CPU)
  kuznechik_init();

  // uart_send("Hello world!\n", 13); // 13 is a number of chars sent: 12 + "\n" 
  // uart_wait_tx_done();

  // set_pin_function(16, FUNC_GPIO);
  // set_gpio_pin_direction(16, DIR_OUT);

  // set_gpio_pin_value(16, 0);

  // set_pin_function(1, FUNC_GPIO);
  // set_gpio_pin_direction(1, DIR_IN);

  unsigned int me2kuznechik[4];
  me2kuznechik[3] = 0x3ee5c99f;
  me2kuznechik[2] = 0x9a41c389;
  me2kuznechik[1] = 0xac17b4fe;
  me2kuznechik[0] = 0x99c72ae4;
  cipher_and_print( me2kuznechik );

  me2kuznechik[3] = 0x79cfed3c;
  me2kuznechik[2] = 0x39fa7677;
  me2kuznechik[1] = 0xb970bb42;
  me2kuznechik[0] = 0xa5631ccd;
  cipher_and_print( me2kuznechik );
}
