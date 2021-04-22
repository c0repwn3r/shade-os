#include "kernel_module_hello_world.h"

void kernel_module_hello_world_load() {
	// load_kern_mods stage 5 invokation is here
	// just print hello, world to screen and exit kernel module
	char hello[] = "Hello, world!";
	print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
	print_str(hello);
	print_newline();
	return; // Always include a return statement, some kernel modules return results.
}

void kernel_module_hello_world_invoke() {
	// This module is not invokable, only runs code on load.
	return;
}

void kernel_module_hello_world_unload() {
	// This module does not have any unload code.
	return;
}
