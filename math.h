#pragma once

#include "types.h"

#include <math.h>

#define PI 3.14159265358979323846264338327950288

typedef union{
    f32 v[3];
    struct{
        float x;
        float y;
        float z;
    };
} vec3;

typedef struct vec3_test{
    f32 v[3];
} vec3_test;

typedef union{
    f32 v[4];
    struct{
        float x;
        float y;
        float z;
        float w;
    };
} vec4;

typedef union{
    f32 v[9];
    struct{
        float m00; float m10; float m20;
        float m01; float m11; float m21;
        float m02; float m12; float m22;
    };
} mat3;

typedef union{
    f32 v[16];
        struct{
        float m00; float m10; float m20; float m30;
        float m01; float m11; float m21; float m31;
        float m02; float m12; float m22; float m32;
        float m03; float m13; float m23; float m33;
    };
} mat4;

mat3 mat3_id();
mat4 mat4_id();
mat4 mat4_mat4_add(mat4 a, mat4 b);
mat4 mat4_mat4_mul(mat4 a, mat4 b);
mat3 mat3_mat3_add(mat3 a, mat3 b);
mat3 mat3_mat3_mul(mat3 a, mat3 b);
vec3 mat3_vec3_mul(mat3 a, vec3 b);
vec4 mat4_vec4_mul(mat4 a, vec4 b);

mat4 perspective_projection(f32 fov, f32 aspect_ratio, f32 z_near, f32 z_far);
mat4 translate_3d(f32 tx, f32 ty, f32 tz);
mat4 rotate_3d(f32 angle, vec3 axis);

f32 rad(f32 deg);