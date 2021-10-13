#pragma once

#include "types.h"
#include "math.h"

#include <assert.h>

typedef union{
    f32 v[3];
    struct{
        f32 r;
        f32 g;
        f32 b;
    };
} RGB;

typedef union{
    f32 v[4];
    struct{
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
} RGBA;

typedef union{
    f32 v_[3];
    struct{
        f32 h;
        f32 s;
        f32 v;
    };
} HSV;

HSV rgb_to_hsv(RGB rgb);
RGB hsv_to_rgb(HSV hsv);