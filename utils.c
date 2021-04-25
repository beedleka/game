#include "utils.h"

void load_file_to_buffer(FILE* file, char** buffer){
    fseek(file, 0, SEEK_END);
    uint32 file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    (*buffer) = malloc(file_size+1);
    fread((*buffer), 1, file_size, file);
    (*buffer)[file_size] = '\0';
}