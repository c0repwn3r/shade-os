#include "print.h"

void kernel_entry() {
  // 64 bit kernel entry - preboot is fully set up
  print_clear(); // Clear screen from bootloader stuff
  print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK); // Set format to classic white on black
  char message[] = "[ OK ] shadeOS 64 bit build - Loaded!";
  print_str(message); // print a little debug message
}
