#define __riscv__
#define LED_DELAY 1000000

#include <stdio.h>

//#include <spi.h>
#include <gpio.h>
#include <uart.h>
//#include <utils.h>
#include <pulpino.h>
#include <vga.h>
#include <vga.h>
#include <mouse.h>

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
  uart_set_cfg(0, 325); // 9600 baud UART, no parity (50MHz CPU)
  init_leds();
  init_switches();

  mouse_init();

  set_gpio_pin_value(16, 1 );

  vga_draw_rect(0, 0, 100, 100);

  uart_wait_tx_done();
  uart_send( "he", 2 );

  while( 1 ){
    char pos[4];
    sprintf( pos, "%d", MOUSE_X_POS );
    uart_wait_tx_done();
    uart_send(pos, 4);
  }

  return 0;
}
