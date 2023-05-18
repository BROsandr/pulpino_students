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

  uart_send("Hello world!\n", 13); // 13 is a number of chars sent: 12 + "\n" 
  uart_wait_tx_done();

  set_pin_function(31, FUNC_GPIO);
  set_gpio_pin_direction(31, DIR_OUT);

  set_gpio_pin_value(31, 0);

  while(1);

  return 0;
}
