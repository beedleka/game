#include "math.h"

mat3 mat3_id(){
    return (mat3){
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
}

mat4 mat4_id(){
    return (mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

mat4 mat4_mat4_add(mat4 a, mat4 b){
    return (mat4){
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2], a.v[3]+b.v[3],
        a.v[4]+b.v[4], a.v[5]+b.v[5], a.v[6]+b.v[6], a.v[7]+b.v[7],
        a.v[8]+b.v[8], a.v[9]+b.v[9], a.v[10]+b.v[10], a.v[11]+b.v[11],
        a.v[12]+b.v[12], a.v[13]+b.v[13], a.v[14]+b.v[14], a.v[15]+b.v[15]
    };
}

mat4 mat4_mat4_mul(mat4 a, mat4 b){
    return (mat4){
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

mat3 mat3_mat3_add(mat3 a, mat3 b){
    return (mat3){
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2],
        a.v[3]+b.v[3], a.v[4]+b.v[4], a.v[5]+b.v[5],
        a.v[6]+b.v[6], a.v[7]+b.v[7], a.v[8]+b.v[8]
    };
}

mat3 mat3_mat3_mul(mat3 a, mat3 b){
    return (mat3){
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

vec3 mat3_vec3_mul(mat3 a, vec3 b){
    return (vec3){
        b.v[0]*a.v[0]+b.v[1]*a.v[3]+b.v[2]*a.v[6],
        b.v[0]*a.v[1]+b.v[1]*a.v[4]+b.v[2]*a.v[7],
        b.v[0]*a.v[2]+b.v[1]*a.v[5]+b.v[2]*a.v[8]
    };
}

vec4 mat4_vec4_mul(mat4 a, vec4 b){
    return (vec4){
        b.v[0]*a.v[0]+b.v[1]*a.v[4]+b.v[2]*a.v[8]+b.v[3]*a.v[12],
        b.v[0]*a.v[1]+b.v[1]*a.v[5]+b.v[2]*a.v[9]+b.v[3]*a.v[13],
        b.v[0]*a.v[2]+b.v[1]*a.v[6]+b.v[2]*a.v[10]+b.v[3]*a.v[14],
        b.v[0]*a.v[3]+b.v[1]*a.v[7]+b.v[2]*a.v[11]+b.v[3]*a.v[15]
    };
}

mat4 perspective_projection(f32 fov, f32 aspect_ratio, f32 z_near, f32 z_far){
    f32 f = 1/tan(fov/2);
    return (mat4){
        f/aspect_ratio, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (z_far+z_near)/(z_near-z_far), -1,
        0, 0, (2*z_far*z_near)/(z_near-z_far), 0
    };
}

mat4 translate_3d(f32 tx, f32 ty, f32 tz){
    return (mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    };
}

mat4 scale_3d(f32 sx, f32 sy, f32 sz){
    return (mat4){
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    };
}

mat4 rotate_3d(f32 angle, vec3 axis){
    f32 c = cos(angle);
    f32 s = sin(angle);
    f32 x = axis.x;
    f32 y = axis.y;
    f32 z = axis.z;
    return (mat4){
        c+x*x*(1-c), y*x*(1-c)+z*s, z*x*(1-c)-y*s, 0,
        x*y*(1-c)-z*s, c+y*y*(1-c), z*y*(1-c)+x*s, 0,
        x*z*(1-c)+y*s, y*z*(1-c)-x*s, c+z*z*(1-c), 0,
        0, 0, 0, 1
    };
}

f32 rad(f32 deg){
    return deg*PI/180;
}