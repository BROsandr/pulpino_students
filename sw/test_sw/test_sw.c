#define __riscv__
#define LED_DELAY 1000000

//#include <spi.h>
#include <gpio.h>
#include <uart.h>
//#include <utils.h>
#include <pulpino.h>
#include <kuznechik.h>


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

  set_pin_function(31, FUNC_GPIO);
  set_gpio_pin_direction(31, DIR_OUT);


  while(1) {
    // char mode = get_gpio_pin_value(1);
    unsigned int me2kuznechik[4];
    me2kuznechik[0] = 0x3ee5c99f;
    me2kuznechik[1] = 0x9a41c389;
    me2kuznechik[2] = 0xac17b4fe;
    me2kuznechik[3] = 0x99c72ae4;

    kuznechik_cipher( me2kuznechik );
    char kuznechik2me[16];
    kuznechik_get_ciphered( (unsigned int *)kuznechik2me );
    // char *reg_addr = 0x00008200;
    // for( int i = 0; i < 16; ++i ) {
    //   *reg_addr = kuznechik2me[i];
    // }
    char buff[17];
    memcpy( buff, kuznechik2me, 16 );
    buff[16] = '\0';
    set_gpio_pin_value(31, 1);
    uart_send( buff, 17 );
  }
}
