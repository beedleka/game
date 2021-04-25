#pragma once

#define pi 3.14159265358979323846264338327950288

typedef struct vec3{
    float v[3];
} vec3;

typedef struct vec4{
    float v[4];
} vec4;

typedef struct mat3{
    float v[9];
} mat3;

typedef struct mat4{
    float v[16];
} mat4;

mat3 mat3_id();
mat4 mat4_id();
mat4 mat4_mat4_add(mat4 a, mat4 b);
mat4 mat4_mat4_mul(mat4 a, mat4 b);
mat3 mat3_mat3_add(mat3 a, mat3 b);
mat3 mat3_mat3_mul(mat3 a, mat3 b);
mat3 mat3_vec3_mul(mat3 a, vec3 b);
mat4 mat4_vec4_mul(mat4 a, vec4 b);