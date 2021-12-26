#include "utils.h"

void load_file_to_buffer(FILE* file, char** buffer){
    fseek(file, 0, SEEK_END);
    u32 file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    (*buffer) = malloc(file_size+1);
    fread((*buffer), 1, file_size, file);
    (*buffer)[file_size] = '\0';
}

u8 str_equals(const char* begin, ptr size, const char* to){
    ptr i = 0;
    for(; i < size; i++, begin++){
        if(*begin != *(to+i)){
            return 0;
        }
    }
    if(*(to+i) != '\0') return 0;
    return 1;
}

void error(const char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR] ");
    fflush(stderr);
    vfprintf(stderr, format, args);
    printf("\n");
    va_end(args);
}

void warn(const char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[WARN] ");
    fflush(stderr);
    vfprintf(stderr, format, args);
    printf("\n");
    va_end(args);
}

void info(const char* format, ...){
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[INFO] ");
    fflush(stderr);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void print_bits_(void* var, size_t type){
    size_t n_bits = type*CHAR_BIT;
    for(size_t i = 0; i < n_bits; i++){
        printf("%"PRIuMAX, ((*(uintmax_t*)var) >> (n_bits-i-1)) & 1);
    }
}