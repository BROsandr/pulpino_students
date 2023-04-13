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

  uart_send("Hello world!\n", 13); // 13 is a number of chars sent: 12 + "\n" 
  uart_wait_tx_done();

  // set_pin_function(16, FUNC_GPIO);
  // set_gpio_pin_direction(16, DIR_OUT);

  // set_gpio_pin_value(16, 0);

  // set_pin_function(1, FUNC_GPIO);
  // set_gpio_pin_direction(1, DIR_IN);

  while(1) {
    // char mode = get_gpio_pin_value(1);
    char me2kuznechik[16];
    for( int i = 0; i < 16; ++i ) {
      me2kuznechik[i] = uart_getchar();
    }

    kuznechik_cipher( (unsigned int *)me2kuznechik );
    char kuznechik2me[16];
    kuznechik_get_ciphered( (unsigned int *)kuznechik2me );
    uart_send( kuznechik2me, 16 );
  }
}
