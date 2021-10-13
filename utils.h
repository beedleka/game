#pragma once

#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print_bits_(void* var, size_t type);
#define print_bits(var) print_bits_(&var, sizeof(var))
void load_file_to_buffer(FILE* file, char** buffer);
u8 str_equals(const char* begin, ptr size, const char* to);
void error(const char* format, ...);
void warn(const char* format, ...);
void info(const char* message, ...);
