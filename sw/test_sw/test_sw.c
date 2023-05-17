#define __riscv__
#define LED_DELAY 1000000

//#include <spi.h>
#include <gpio.h>
#include <uart.h>
//#include <utils.h>
#include <pulpino.h>
#include <vga.h>

#define DEMO_SW 0
#define RESET_SW 1

void cipher_and_print( unsigned int data[4] ) {
  kuznechik_cipher( data );
  char kuznechik2me[16];
  kuznechik_get_ciphered( (unsigned int *)kuznechik2me );
  char buff[16];
  for( int i = 0; i < 16; ++i ) {
    buff[15-i] = kuznechik2me[i];
  }
  uart_wait_tx_done();
  uart_send( buff, 16 );
}

void demo_cipher() {
  unsigned int me2kuznechik[4];
  me2kuznechik[3] = 0x3ee5c99f;
  me2kuznechik[2] = 0x9a41c389;
  me2kuznechik[1] = 0xac17b4fe;
  me2kuznechik[0] = 0x99c72ae4;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(16, 1);

  me2kuznechik[3] = 0x79cfed3c;
  me2kuznechik[2] = 0x39fa7677;
  me2kuznechik[1] = 0xb970bb42;
  me2kuznechik[0] = 0xa5631ccd;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(17, 1);

  me2kuznechik[3] = 0x63a148b3;
  me2kuznechik[2] = 0xd9774ced;
  me2kuznechik[1] = 0xe1c54673;
  me2kuznechik[0] = 0xc68dcd03;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(18, 1);

  me2kuznechik[3] = 0x2ed02c74;
  me2kuznechik[2] = 0x160391fd;
  me2kuznechik[1] = 0x9e8bd4ba;
  me2kuznechik[0] = 0x21e79a9d;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(19, 1);

  me2kuznechik[3] = 0x74f24530;
  me2kuznechik[2] = 0x59092269;
  me2kuznechik[1] = 0x22ac9d24;
  me2kuznechik[0] = 0xb9ed3b20;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(20, 1);

  me2kuznechik[3] = 0x03dde21c;
  me2kuznechik[2] = 0x095413db;
  me2kuznechik[1] = 0x093bb863;
  me2kuznechik[0] = 0x6d8fc082;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(21, 1);

  me2kuznechik[3] = 0xbdeb379c;
  me2kuznechik[2] = 0x9326a275;
  me2kuznechik[1] = 0xc58c7568;
  me2kuznechik[0] = 0x85c40d47;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(22, 1);

  me2kuznechik[3] = 0x2dcabdf6;
  me2kuznechik[2] = 0xb6488f5f;
  me2kuznechik[1] = 0x3d56c2fd;
  me2kuznechik[0] = 0x3d2357b0;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(23, 1);

  me2kuznechik[3] = 0x887adf8b;
  me2kuznechik[2] = 0x545c4334;
  me2kuznechik[1] = 0xe0070c63;
  me2kuznechik[0] = 0xd2f344a3;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(24, 1);

  me2kuznechik[3] = 0x23feeb91;
  me2kuznechik[2] = 0x15fab3e4;
  me2kuznechik[1] = 0xf9739578;
  me2kuznechik[0] = 0x010f212c;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(25, 1);

  me2kuznechik[3] = 0x53e0ebee;
  me2kuznechik[2] = 0x97b0c1b8;
  me2kuznechik[1] = 0x377ac5bc;
  me2kuznechik[0] = 0xe14cb4e8;
  cipher_and_print( me2kuznechik );
  set_gpio_pin_value(26, 1);
}

void init_leds() {
  for( int i = 0; i < 16; ++i ) {
    set_pin_function(16+i, FUNC_GPIO);
    set_gpio_pin_direction(16+i, DIR_OUT);
  }
}

void init_switches() {
  for( int i = 0; i < 16; ++i ) {
    set_pin_function(i, FUNC_GPIO);
    set_gpio_pin_direction(i, DIR_IN);
  }
}

void reset_leds() {
  for( int i = 0; i < 16; ++i ) {
    set_gpio_pin_value(16+i, 0);
  }
}

int main()
{
  init_leds();
  init_switches();

  set_gpio_pin_value(16, 1 );

  vga_draw_rect(0, 0, 100, 100);

  return 0;
}
