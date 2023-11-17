
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

  set_gpio_pin_value(31, 0);

  uint8_t* vga_buff = VGA_BASE_ADDR;

  while(1) {
    *VGA_BASE_ADDR = 0x41;
  }
}
