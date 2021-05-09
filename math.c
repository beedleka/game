#include "math.h"

Mat3 Mat3_id(){
    return (Mat3){
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
}

Mat4 Mat4_id(){
    return (Mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Mat4 Mat4_Mat4_add(Mat4 a, Mat4 b){
    return (Mat4){
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2], a.v[3]+b.v[3],
        a.v[4]+b.v[4], a.v[5]+b.v[5], a.v[6]+b.v[6], a.v[7]+b.v[7],
        a.v[8]+b.v[8], a.v[9]+b.v[9], a.v[10]+b.v[10], a.v[11]+b.v[11],
        a.v[12]+b.v[12], a.v[13]+b.v[13], a.v[14]+b.v[14], a.v[15]+b.v[15]
    };
}

Mat4 Mat4_Mat4_mul(Mat4 a, Mat4 b){
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

Mat3 Mat3_Mat3_add(Mat3 a, Mat3 b){
    return (Mat3){
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2],
        a.v[3]+b.v[3], a.v[4]+b.v[4], a.v[5]+b.v[5],
        a.v[6]+b.v[6], a.v[7]+b.v[7], a.v[8]+b.v[8]
    };
}

Mat3 Mat3_Mat3_mul(Mat3 a, Mat3 b){
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

Vec3 Mat3_Vec3_mul(Mat3 a, Vec3 b){
    return (Vec3){
        b.v[0]*a.v[0]+b.v[1]*a.v[3]+b.v[2]*a.v[6],
        b.v[0]*a.v[1]+b.v[1]*a.v[4]+b.v[2]*a.v[7],
        b.v[0]*a.v[2]+b.v[1]*a.v[5]+b.v[2]*a.v[8]
    };
}

Vec4 Mat4_Vec4_mul(Mat4 a, Vec4 b){
    return (Vec4){
        b.v[0]*a.v[0]+b.v[1]*a.v[4]+b.v[2]*a.v[8]+b.v[3]*a.v[12],
        b.v[0]*a.v[1]+b.v[1]*a.v[5]+b.v[2]*a.v[9]+b.v[3]*a.v[13],
        b.v[0]*a.v[2]+b.v[1]*a.v[6]+b.v[2]*a.v[10]+b.v[3]*a.v[14],
        b.v[0]*a.v[3]+b.v[1]*a.v[7]+b.v[2]*a.v[11]+b.v[3]*a.v[15]
    };
}

Mat4 perspective_projection(f32 fov, f32 aspect_ratio, f32 z_near, f32 z_far){
    f32 f = 1/tan(fov/2);
    return (Mat4){
        f/aspect_ratio, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (z_far+z_near)/(z_near-z_far), -1,
        0, 0, (2*z_far*z_near)/(z_near-z_far), 0
    };
}

Mat4 translate_3d(Vec3 t){
    return (Mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        t.x, t.y, t.z, 1
    };
}

Mat4 scale_3d(Vec3 s){
    return (Mat4){
        s.x, 0, 0, 0,
        0, s.y, 0, 0,
        0, 0, s.z, 0,
        0, 0, 0, 1
    };
}

Mat4 rotate_3d(Vec3 r){
    return (Mat4){
        cos(r.y)*cos(r.z), cos(r.y)*sin(r.z), -sin(r.y), 0,
        sin(r.x)*sin(r.y)*cos(r.z)-cos(r.x)*sin(r.z), sin(r.x)*sin(r.y)*sin(r.z)+cos(r.x)*cos(r.z), sin(r.x)*cos(r.y), 0,
        cos(r.x)*sin(r.y)*cos(r.z)+sin(r.x)*sin(r.z), cos(r.x)*sin(r.y)*sin(r.z)-sin(r.x)*cos(r.z), cos(r.x)*cos(r.y), 0,
        0, 0, 0, 1
    };
}

f32 rad(f32 deg){
    return deg*PI/180;
}