#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t uint64;
typedef int64_t int64;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;
typedef double float64;

void load_file_to_buffer(FILE* file, char** buffer);