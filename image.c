#include "image.h"

u8* load_image(const char* image_filepath, u32* width, u32* height, u8* channels){
    FILE* image_file = fopen(image_filepath, "rb");
    if(image_file == NULL){
        error("load_image: no such file or directory \"%s\"", image_filepath);
        return NULL;
    }

    u8* image_data;
    fseek(image_file, 0, SEEK_END);
    u32 file_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    image_data = malloc(file_size*sizeof(u8));
    if(image_data == NULL){
        error("load_image: can't allocate memory");
        fclose(image_file);
        return NULL;
    }

    fread(image_data, 1, file_size, image_file);
    if(image_data[0] != 0x54 || image_data[1] != 0x45 || image_data[2] != 0x58){
        error("load_image: invalid image file \"%s\"", image_filepath);
        fclose(image_file);
        free(image_data);
        return NULL;
    }

    *width = (image_data[3]<<24)+(image_data[4]<<16)+(image_data[5]<<8)+image_data[6];
    *height = (image_data[7]<<24)+(image_data[8]<<16)+(image_data[9]<<8)+image_data[10];
    *channels = image_data[11];
    image_data += 12;
    fclose(image_file);
    return image_data;
}

void free_image(u8* image_data){
    image_data -= 12;
    free(image_data);
}