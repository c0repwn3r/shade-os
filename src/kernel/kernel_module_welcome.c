#include "kernel_module_welcome.h"

void kernel_module_welcome_load() {
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
    return;
}

void kernel_module_welcome_invoke() {
    return;
}

void kernel_module_welcome_unload() {
    return;
}
