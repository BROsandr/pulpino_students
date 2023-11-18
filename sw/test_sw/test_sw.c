
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

  uint32_t* vga_buff = (uint32_t*)VGA_BASE_ADDR;

  // Fill the screen with 0. Mark the end with 1.
  for (int i = 0; i < 60; ++i) {
    for (int j = 0; j < 80; j += 4) {
      if (i == 59 && j == 76) *vga_buff = (0x30 << 24 ) | (0x30 << 16 ) | (0x30 << 8 ) | 0x31;
      else                    *vga_buff = (0x30 << 24 ) | (0x30 << 16 ) | (0x30 << 8 ) | 0x30;
      ++vga_buff;
    }
  }

  while(1) {
    asm volatile ("nop");
  }
}
