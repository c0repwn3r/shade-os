#pragma once

#include <stdint.h> // Standard integers
#include <stddef.h> // Standard definitions

#include "print.h" // Include print header

void kernel_debug(char* string); // [ DEBUG ] Message
void kernel_ok(char* string); // [ OK ] Message
void kernel_warn(char* string); // [ WARN ] Message
void kernel_error(char* string); // [ FAILED ] Message
void kernel_fatal(char* string); // [ FATAL ] Message

void process_debug(char* thread, char* message); // [ DEBUG/Thread ] Message
