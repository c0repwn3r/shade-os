#pragma once

#include <stdint.h> // Standard integers
#include <stddef.h> // Standard definitions

#include "print.h" // Include print header

enum {
  LOG_LEVEL_DEBUG = 4;
  LOG_LEVEL_OK = 3;
  LOG_LEVEL_WARN = 2;
  LOG_LEVEL_ERROR = 1;
  LOG_LEVEL_FATAL = 0;
}

void kernel_debug(char* string); // [ DEBUG ] Message
void kernel_ok(char* string); // [ OK ] Message
void kernel_warn(char* string); // [ WARN ] Message
void kernel_error(char* string); // [ FAILED ] Message
void kernel_fatal(char* string); // [ FATAL ] Message

void thread_debug(char* thread, char* message); // [ DEBUG/Thread ] Message
void thread_ok(char* thread, char* message); // [ Thread ] Message
void thread_warn(char* thread, char* message); // [ WARN/Thread ] Message
void thread_error(char* thread, char* message); // [ ERROR/Thread ] Message
void thread_fatal(char* thread, char* message); // [ FATAL/Thread ] Message
