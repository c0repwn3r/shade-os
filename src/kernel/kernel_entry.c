#include "print.h"

void kernel_entry() {
  // 64 bit kernel entry - preboot is fully set up
  print_clear(); // Clear screen from bootloader stuff
  print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK); // Set format to classic white on black
  print_str("shadeOS in 64 bit kernel - debug build"); // print a little debug message
}
