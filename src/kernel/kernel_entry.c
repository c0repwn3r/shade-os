#include "print.h"
#include "shade-ver.h"

void kernel_msg_ok(char* msg) {
	char ok_p1[] = "[ ";
	char ok_p2[] = "OK ";
	char ok_p3[] = "] ";
	print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
	print_str(ok_p1);
	print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
	print_str(ok_p2);
	print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
	print_str(ok_p3);
	print_str(msg);
}

void load_kernel_modules() {
	// stage-5 prep-kernel-mods
	// Call kernel_module_something_load() functions here
	
	// stage5 prep-kernel-mods finished, boot sequence completed
}

void kernel_welcome() {
	print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
	char wlc[] = "Welcome to ";
	char wlc2[] = "Shade";
	char wlc3[] = "!\n";
	print_str(wlc);
	print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLACK);
	print_str(wlc2);
	print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
	print_str(wlc3);
	print_newline();
	char version[] = "shadeOS kernel version ";
	print_str(version);
	print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
	print_str(SHADEOS_KERNEL_VERSION_STRING);
	print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
	print_newline();
	char build[] = "Running on ";
	print_str(build);
	print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
	print_str(SHADEOS_BUILD_NAME_STRING);
	print_newline();
}

void kernel_entry() {
  // 64 bit kernel entry - preboot is fully set up
  print_clear(); // Clear screen from bootloader stuff
  print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK); // Set format to classic white on black
  load_kernel_modules();
  char kernmods[] = "Loaded kernel modules.\n";
  kernel_msg_ok(kernmods);
  kernel_welcome();
  char message[] = "Stage 5 finished. Kernel operational.\n";
  kernel_msg_ok(message);
  print_newline();
  // time for some REAL code
}
