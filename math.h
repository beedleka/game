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
    struct{
        float r;
        float g;
        float b;
    };
} Vec3;

typedef union{
    f32 v[4];
    struct{
        float x;
        float y;
        float z;
        float w;
    };
    struct{
        float r;
        float g;
        float b;
        float a;
    };
} Vec4;

typedef union{
    f32 v[9];
    struct{
        float m00; float m10; float m20;
        float m01; float m11; float m21;
        float m02; float m12; float m22;
    };
} Mat3;

typedef union{
    f32 v[16];
        struct{
        float m00; float m10; float m20; float m30;
        float m01; float m11; float m21; float m31;
        float m02; float m12; float m22; float m32;
        float m03; float m13; float m23; float m33;
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
Mat4 rotate_3d(f32 angle, Vec3 axis);

f32 rad(f32 deg);