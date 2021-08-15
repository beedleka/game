#pragma once

#include "types.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

u8* load_image(const char* image_filepath, u32* width, u32* height, u8* channels);
void free_image(u8* image_data);