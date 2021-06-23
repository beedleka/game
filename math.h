#pragma once

#include "types.h"

#include <math.h>

#define PI 3.14159265358979323846264338327950288
#define PI2 6.28318530717958647692528676655900576

#ifndef max
#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif
#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

typedef union{
    f32 v[2];
    struct{
        f32 x;
        f32 y;
    };
} Vec2;

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

typedef Vec4 Quaternion;

typedef union{
    f32 m[9];
    struct{
        f32 m00; f32 m10; f32 m20;
        f32 m01; f32 m11; f32 m21;
        f32 m02; f32 m12; f32 m22;
    };
} Mat3;

typedef union{
    f32 m[16];
    struct{
        f32 m00; f32 m10; f32 m20; f32 m30;
        f32 m01; f32 m11; f32 m21; f32 m31;
        f32 m02; f32 m12; f32 m22; f32 m32;
        f32 m03; f32 m13; f32 m23; f32 m33;
    };
} Mat4;

Mat3 mat3_id();
Mat3 mat3_mat3_add(Mat3 a, Mat3 b);
Mat3 mat3_mat3_mul(Mat3 a, Mat3 b);
Vec3 mat3_vec3_mul(Mat3 a, Vec3 b);

Mat4 mat4_id();
Mat4 mat4_mat4_add(Mat4 a, Mat4 b);
Mat4 mat4_mat4_mul(Mat4 a, Mat4 b);
Vec4 mat4_vec4_mul(Mat4 a, Vec4 b);

Vec3 vec3_cross(Vec3 a, Vec3 b);
f32 vec3_dot(Vec3 a, Vec3 b);
f32 vec3_magnitude(Vec3 v);
Vec3 vec3_normalize(Vec3 v);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 v, f32 s);
Vec3 vec3_lerp(Vec3 a, Vec3 b, f32 t);

f32 vec4_magnitude(Vec4 v);
Vec4 vec4_normalize(Vec4 v);

Quaternion quat_id();
Quaternion euler_to_quat(Vec3 e);
Quaternion quat_mul(Quaternion a, Quaternion b);
f32 quat_magnitude(Quaternion q);
Quaternion quat_normalize(Quaternion q);
Quaternion quat_conjugate(Quaternion q);
Quaternion quat_inverse(Quaternion q);
Quaternion quat_difference(Quaternion a, Quaternion b);
Quaternion quat_exp(Quaternion q);
Quaternion quat_log(Quaternion q);
Quaternion quat_scale(Quaternion q, f32 s);
Quaternion quat_pow(Quaternion q, f32 n);
Quaternion quat_slerp(Quaternion q1, Quaternion q2, f32 t);
f32 quat_dot_product(Quaternion q1, Quaternion q2);

Mat4 perspective_projection_matrix(f32 fov, f32 aspect_ratio, f32 z_near, f32 z_far);
Mat4 translate_3d_matrix(Vec3 t);
Mat4 scale_3d_matrix(Vec3 s);
Mat4 rotate_3d_matrix(Quaternion q);
Mat4 lookat_matrix(Vec3 camera_pos, Vec3 target_pos, Vec3 world_up);

f32 rad(f32 deg);