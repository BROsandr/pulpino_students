
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

  volatile uint32_t* vga_buff = (uint32_t*)VGA_BASE_ADDR;

  // Fill the screen with 0. Mark the end with 1.
  for (int i = 0; i < 30; ++i) {
    for (int j = 0; j < 80; ++j) {
      if (i == 29 && j == 79) *vga_buff = (0xfa << 8) | (0x31);
      else                    *vga_buff = (0xab << 8) | (0x30);
      ++vga_buff;
    }
  }
  set_gpio_pin_value(16, 1);

  // check written chars and colors
  vga_buff = (uint32_t*)VGA_BASE_ADDR;
  char fail = 0;
  for (int i = 0; i < 30; ++i) {
    for (int j = 0; j < 80; ++j) {
      uint32_t el = *vga_buff;
      if (i == 29 && j == 79) {
        if ((((el >> 8) & 0xff) != 0xfa) || (el & 0xff) != 0x31) {
          set_gpio_pin_value(30, 1);
          fail = 1;
          goto end;
        }
      } else {
        if ((((el >> 8) & 0xff) != 0xab) || (el & 0xff) != 0x30) {
          set_gpio_pin_value(29, 1);
          fail = 1;
          goto end;
        }
      }
      ++vga_buff;
    }
  }

end:
  if (!fail) set_gpio_pin_value(28, 1);


  uart_set_cfg(0, 325); // 9600 baud UART, no parity (50MHz CPU)


  while(1) {
    vga_buff = (uint32_t*)VGA_BASE_ADDR;
    // uart_sendchar(ch);
    for (int i = 0; i < 30; ++i) {
      for (int j = 0; j < 80; ++j) {
        char ch;
        char color;
        ch = uart_getchar();
        color = uart_getchar();
        set_gpio_pin_value(27, 1);
        *vga_buff = (color << 8) | ch;
        ++vga_buff;
      }
    }
    set_gpio_pin_value(26, 1);
  }
}
