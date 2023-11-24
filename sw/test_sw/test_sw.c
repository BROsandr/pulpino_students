
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

  volatile int* vga_ch_map = (int*)VGA_CH_MAP_BASE_ADDR;

  // Fill the screen with 0. Mark the end with 1.
  for (int i = 0; i < (2400 / 4); ++i) {
    if   (i == (2400 / 4 - 1)) *vga_ch_map = 0x30303031;
    else                       *vga_ch_map = 0x30303030;
    ++vga_ch_map;
  }
  set_gpio_pin_value(16, 1);

  volatile int* vga_col_map = (uint32_t*)VGA_COL_MAP_BASE_ADDR;
  for (int i = 0; i < (2400 / 4); ++i) {
    if   (i == (2400 / 4 - 1)) *vga_col_map = 0xabababfa;
    else                       *vga_col_map = 0xabababab;
    ++vga_col_map;
  }
  set_gpio_pin_value(17, 1);

  // check written chars and colors
  vga_ch_map = (int*)VGA_CH_MAP_BASE_ADDR;
  char fail = 0;
  for (int i = 0; i < (2400 / 4); ++i) {
    uint32_t el = *vga_ch_map;
    if (i == (2400 / 4 - 1)) {
      if (el != 0x30303031) {
        set_gpio_pin_value(30, 1);
        fail = 1;
        goto end;
      }
    } else {
      if (el != 0x30303030) {
        set_gpio_pin_value(29, 1);
        fail = 1;
        goto end;
      }
    }
    ++vga_ch_map;
  }

  vga_col_map = (uint32_t*)VGA_COL_MAP_BASE_ADDR;
  for (int i = 0; i < (2400 / 4); ++i) {
      uint32_t el = *vga_col_map;
      if (i == (2400 / 4 - 1)) {
        if (el != 0xabababfa) {
          set_gpio_pin_value(28, 1);
          fail = 1;
          goto end;
        }
      } else {
        if (el != 0xabababab) {
          set_gpio_pin_value(27, 1);
          fail = 1;
          goto end;
        }
      }
      ++vga_col_map;
  }

end:
  if (!fail) set_gpio_pin_value(26, 1);


  uart_set_cfg(0, 325); // 9600 baud UART, no parity (50MHz CPU)


  while(1) {
    vga_ch_map = (int*)VGA_CH_MAP_BASE_ADDR;
    vga_col_map = (uint32_t*)VGA_COL_MAP_BASE_ADDR;
    // uart_sendchar(ch);
    for (int i = 0; i < (2400 / 4); ++i) {
      char ch;
      char color;
      ch = uart_getchar();
      color = uart_getchar();
      set_gpio_pin_value(25, 1);
      *vga_ch_map  = ch << 24 | ch << 16 | ch << 8 | ch;
      *vga_col_map = color << 24 | color << 16 | color << 8 | color;
      ++vga_ch_map;
      ++vga_col_map;
    }
    set_gpio_pin_value(24, 1);
  }
}
