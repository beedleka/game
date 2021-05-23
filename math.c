#include "math.h"

Mat3 mat3_id(){
    return (Mat3){
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
}

Mat4 mat4_id(){
    return (Mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Quaternion quat_id(){
    return (Quaternion){0, 0, 0, 1};
}

Mat4 mat4_mat4_add(Mat4 a, Mat4 b){
    return (Mat4){
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2], a.v[3]+b.v[3],
        a.v[4]+b.v[4], a.v[5]+b.v[5], a.v[6]+b.v[6], a.v[7]+b.v[7],
        a.v[8]+b.v[8], a.v[9]+b.v[9], a.v[10]+b.v[10], a.v[11]+b.v[11],
        a.v[12]+b.v[12], a.v[13]+b.v[13], a.v[14]+b.v[14], a.v[15]+b.v[15]
    };
}

Mat4 mat4_mat4_mul(Mat4 a, Mat4 b){
    return (Mat4){
        a.v[0]*b.v[0]+a.v[1]*b.v[4]+a.v[2]*b.v[8]+a.v[3]*b.v[12],
        a.v[0]*b.v[1]+a.v[1]*b.v[5]+a.v[2]*b.v[9]+a.v[3]*b.v[13],
        a.v[0]*b.v[2]+a.v[1]*b.v[6]+a.v[2]*b.v[10]+a.v[3]*b.v[14],
        a.v[0]*b.v[3]+a.v[1]*b.v[7]+a.v[2]*b.v[11]+a.v[3]*b.v[15],

        a.v[4]*b.v[0]+a.v[5]*b.v[4]+a.v[6]*b.v[8]+a.v[7]*b.v[12],
        a.v[4]*b.v[1]+a.v[5]*b.v[5]+a.v[6]*b.v[9]+a.v[7]*b.v[13],
        a.v[4]*b.v[2]+a.v[5]*b.v[6]+a.v[6]*b.v[10]+a.v[7]*b.v[14],
        a.v[4]*b.v[3]+a.v[5]*b.v[7]+a.v[6]*b.v[11]+a.v[7]*b.v[15],

        a.v[8]*b.v[0]+a.v[9]*b.v[4]+a.v[10]*b.v[8]+a.v[11]*b.v[12],
        a.v[8]*b.v[1]+a.v[9]*b.v[5]+a.v[10]*b.v[9]+a.v[11]*b.v[13],
        a.v[8]*b.v[2]+a.v[9]*b.v[6]+a.v[10]*b.v[10]+a.v[11]*b.v[14],
        a.v[8]*b.v[3]+a.v[9]*b.v[7]+a.v[10]*b.v[11]+a.v[11]*b.v[15],

        a.v[12]*b.v[0]+a.v[13]*b.v[4]+a.v[14]*b.v[8]+a.v[15]*b.v[12],
        a.v[12]*b.v[1]+a.v[13]*b.v[5]+a.v[14]*b.v[9]+a.v[15]*b.v[13],
        a.v[12]*b.v[2]+a.v[13]*b.v[6]+a.v[14]*b.v[10]+a.v[15]*b.v[14],
        a.v[12]*b.v[3]+a.v[13]*b.v[7]+a.v[14]*b.v[11]+a.v[15]*b.v[15]
    };
}

Mat3 mat3_mat3_add(Mat3 a, Mat3 b){
    return (Mat3){
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2],
        a.v[3]+b.v[3], a.v[4]+b.v[4], a.v[5]+b.v[5],
        a.v[6]+b.v[6], a.v[7]+b.v[7], a.v[8]+b.v[8]
    };
}

Mat3 mat3_mat3_mul(Mat3 a, Mat3 b){
    return (Mat3){
        a.v[0]*b.v[0]+a.v[1]*b.v[3]+a.v[2]*b.v[6],
        a.v[0]*b.v[1]+a.v[1]*b.v[4]+a.v[2]*b.v[7],
        a.v[0]*b.v[2]+a.v[1]*b.v[5]+a.v[2]*b.v[8],

        a.v[3]*b.v[0]+a.v[4]*b.v[3]+a.v[5]*b.v[6],
        a.v[3]*b.v[1]+a.v[4]*b.v[4]+a.v[5]*b.v[7],
        a.v[3]*b.v[2]+a.v[4]*b.v[5]+a.v[5]*b.v[8],

        a.v[6]*b.v[0]+a.v[7]*b.v[3]+a.v[8]*b.v[6],
        a.v[6]*b.v[1]+a.v[7]*b.v[4]+a.v[8]*b.v[7],
        a.v[6]*b.v[2]+a.v[7]*b.v[5]+a.v[8]*b.v[8]
    };
}

Vec3 mat3_vec3_mul(Mat3 a, Vec3 b){
    return (Vec3){
        b.v[0]*a.v[0]+b.v[1]*a.v[3]+b.v[2]*a.v[6],
        b.v[0]*a.v[1]+b.v[1]*a.v[4]+b.v[2]*a.v[7],
        b.v[0]*a.v[2]+b.v[1]*a.v[5]+b.v[2]*a.v[8]
    };
}

Vec4 mat4_vec4_mul(Mat4 a, Vec4 b){
    return (Vec4){
        b.v[0]*a.v[0]+b.v[1]*a.v[4]+b.v[2]*a.v[8]+b.v[3]*a.v[12],
        b.v[0]*a.v[1]+b.v[1]*a.v[5]+b.v[2]*a.v[9]+b.v[3]*a.v[13],
        b.v[0]*a.v[2]+b.v[1]*a.v[6]+b.v[2]*a.v[10]+b.v[3]*a.v[14],
        b.v[0]*a.v[3]+b.v[1]*a.v[7]+b.v[2]*a.v[11]+b.v[3]*a.v[15]
    };
}

Mat4 perspective_projection_matrix(f32 fov, f32 aspect_ratio, f32 z_near, f32 z_far){
    f32 f = 1/tan(fov/2);
    return (Mat4){
        f/aspect_ratio, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (z_far+z_near)/(z_near-z_far), -1,
        0, 0, (2*z_far*z_near)/(z_near-z_far), 0
    };
}

Mat4 translate_3d_matrix(Vec3 t){
    return (Mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        t.x, t.y, t.z, 1
    };
}

Mat4 scale_3d_matrix(Vec3 s){
    return (Mat4){
        s.x, 0, 0, 0,
        0, s.y, 0, 0,
        0, 0, s.z, 0,
        0, 0, 0, 1
    };
}

Mat4 rotate_3d_matrix(Quaternion q){
    f32 xx = q.x*q.x;
    f32 yy = q.y*q.y;
    f32 zz = q.z*q.z;
    return (Mat4){
        1-2*yy-2*zz, 2*q.x*q.y+2*q.z*q.w, 2*q.x*q.z-2*q.y*q.w, 0,
        2*q.x*q.y-2*q.z*q.w, 1-2*xx-2*zz, 2*q.y*q.z+2*q.x*q.w, 0,
        2*q.x*q.z+2*q.y*q.w, 2*q.y*q.z-2*q.x*q.w, 1-2*xx-2*yy, 0,
        0, 0, 0, 1
    };
}

Quaternion euler_to_quat(Vec3 e){
    f32 cx = cos(e.x/2);
    f32 sx = sin(e.x/2);
    f32 cy = cos(e.y/2);
    f32 sy = sin(e.y/2);
    f32 cz = cos(e.z/2);
    f32 sz = sin(e.z/2);
    return (Quaternion){
        cx*cy*cz+sx*sy*sz,
        sx*cy*cz-cx*sy*sz,
        cx*sy*cz+sx*cy*sz,
        cx*cy*sz-sx*sy*cz
    };
}

Quaternion quat_quat_mul(Quaternion a, Quaternion b){
    return (Quaternion){
        a.w*b.x+a.x*b.w+a.y*b.z-a.z*b.y,
        a.w*b.y-a.x*b.z+a.y*b.w+a.z*b.x,
        a.w*b.z+a.x*b.y-a.y*b.x+a.z*b.w,
        a.w*b.w-a.x*b.x-a.y*b.y-a.z*b.z
    };
}

f32 rad(f32 deg){
    return deg*PI/180;
}

Vec3 vec3_cross_product(Vec3 a, Vec3 b){
    return (Vec3){
        a.y*b.z-a.z*b.y,
        a.z*b.x-a.x*b.z,
        a.x*b.y-a.y*b.x
    };
}

f32 vec3_magnitude(Vec3 v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

f32 vec4_magnitude(Vec4 v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

f32 quat_magnitude(Quaternion q){
    return sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

f32 vec3_dot_product(Vec3 a, Vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3 vec3_normalize(Vec3 v){
    f32 m = vec3_magnitude(v);
    return (Vec3){
        v.x/m,
        v.y/m,
        v.z/m
    };
}

Vec4 vec4_normalize(Vec4 v){
    f32 m = vec4_magnitude(v);
    return (Vec4){
        v.x/m,
        v.y/m,
        v.z/m,
        v.w/m
    };
}

Quaternion quat_normalize(Quaternion q){
    f32 m = quat_magnitude(q);
    return (Quaternion){
        q.x/m,
        q.y/m,
        q.z/m,
        q.w/m
    };
}