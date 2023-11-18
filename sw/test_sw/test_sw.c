
#define __riscv__
#define LED_DELAY 1000000

//#include <spi.h>
#include <gpio.h>
#include <uart.h>
//#include <utils.h>
#include <pulpino.h>


int main()
{

  set_pin_function(31, FUNC_GPIO);
  set_gpio_pin_direction(31, DIR_OUT);

  set_gpio_pin_value(31, 1);

  uint8_t* vga_buff = (uint8_t*)VGA_BASE_ADDR;

  *vga_buff = 0x41;

  while(1) {
    asm volatile ("nop");
  }
}
