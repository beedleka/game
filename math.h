#pragma once

#include "types.h"

#include <math.h>

#define PI 3.14159265358979323846264338327950288

typedef union{
    f32 v[3];
    struct{
        f32 x;
        f32 y;
        f32 z;
    };
    struct{
        f32 r;
        f32 g;
        f32 b;
    };
} Vec3;

typedef union{
    f32 v[4];
    struct{
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    struct{
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
} Vec4;

typedef union{
    f32 v[9];
    struct{
        f32 m00; f32 m10; f32 m20;
        f32 m01; f32 m11; f32 m21;
        f32 m02; f32 m12; f32 m22;
    };
} Mat3;

typedef union{
    f32 v[16];
        struct{
        f32 m00; f32 m10; f32 m20; f32 m30;
        f32 m01; f32 m11; f32 m21; f32 m31;
        f32 m02; f32 m12; f32 m22; f32 m32;
        f32 m03; f32 m13; f32 m23; f32 m33;
    };
} Mat4;

Mat3 Mat3_id();
Mat4 Mat4_id();
Mat4 Mat4_Mat4_add(Mat4 a, Mat4 b);
Mat4 Mat4_Mat4_mul(Mat4 a, Mat4 b);
Mat3 Mat3_Mat3_add(Mat3 a, Mat3 b);
Mat3 Mat3_Mat3_mul(Mat3 a, Mat3 b);
Vec3 Mat3_Vec3_mul(Mat3 a, Vec3 b);
Vec4 Mat4_Vec4_mul(Mat4 a, Vec4 b);

Mat4 perspective_projection(f32 fov, f32 aspect_ratio, f32 z_near, f32 z_far);
Mat4 translate_3d(Vec3 t);
Mat4 scale_3d(Vec3 s);
Mat4 rotate_3d(Vec3 r);

f32 rad(f32 deg);