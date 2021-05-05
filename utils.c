#include "utils.h"

void load_file_to_buffer(FILE* file, char** buffer){
    fseek(file, 0, SEEK_END);
    u32 file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    (*buffer) = malloc(file_size+1);
    fread((*buffer), 1, file_size, file);
    (*buffer)[file_size] = '\0';
}

int str_equals(const char* begin, ptr size, const char* to){
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
    printf("[ERROR] ");
    fflush(stdout);
    vfprintf(stderr, format, args);
    printf("\n");
    va_end(args);
}

void warn(const char* format, ...){
    va_list args;
    va_start(args, format);
    printf("[WARN] ");
    fflush(stdout);
    vfprintf(stderr, format, args);
    printf("\n");
    va_end(args);
}

void info(const char* format, ...){
    va_list args;
    va_start(args, format);
    printf("[INFO] ");
    fflush(stdout);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}