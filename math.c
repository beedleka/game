#include "math.h"

mat3 mat3_id(){
    return (mat3){{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    }};
}

mat4 mat4_id(){
    return (mat4){{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
}

mat4 mat4_mat4_add(mat4 a, mat4 b){
    return (mat4){{
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2], a.v[3]+b.v[3],
        a.v[4]+b.v[4], a.v[5]+b.v[5], a.v[6]+b.v[6], a.v[7]+b.v[7],
        a.v[8]+b.v[8], a.v[9]+b.v[9], a.v[10]+b.v[10], a.v[11]+b.v[11],
        a.v[12]+b.v[12], a.v[13]+b.v[13], a.v[14]+b.v[14], a.v[15]+b.v[15]
    }};
}

mat4 mat4_mat4_mul(mat4 a, mat4 b){
    return (mat4){{
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
    }};
}

mat3 mat3_mat3_add(mat3 a, mat3 b){
    return (mat3){{
        a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2],
        a.v[3]+b.v[3], a.v[4]+b.v[4], a.v[5]+b.v[5],
        a.v[6]+b.v[6], a.v[7]+b.v[7], a.v[8]+b.v[8]
    }};
}

mat3 mat3_mat3_mul(mat3 a, mat3 b){
    return (mat3){{
        a.v[0]*b.v[0]+a.v[1]*b.v[3]+a.v[2]*b.v[6],
        a.v[0]*b.v[1]+a.v[1]*b.v[4]+a.v[2]*b.v[7],
        a.v[0]*b.v[2]+a.v[1]*b.v[5]+a.v[2]*b.v[8],

        a.v[3]*b.v[0]+a.v[4]*b.v[3]+a.v[5]*b.v[6],
        a.v[3]*b.v[1]+a.v[4]*b.v[4]+a.v[5]*b.v[7],
        a.v[3]*b.v[2]+a.v[4]*b.v[5]+a.v[5]*b.v[8],

        a.v[6]*b.v[0]+a.v[7]*b.v[3]+a.v[8]*b.v[6],
        a.v[6]*b.v[1]+a.v[7]*b.v[4]+a.v[8]*b.v[7],
        a.v[6]*b.v[2]+a.v[7]*b.v[5]+a.v[8]*b.v[8]
    }};
}

mat3 mat3_vec3_mul(mat3 a, vec3 b){
    return (mat3){{
        a.v[0]*b.v[0]+a.v[1]*b.v[3]+a.v[2]*b.v[6],
        a.v[0]*b.v[1]+a.v[1]*b.v[4]+a.v[2]*b.v[7],
        a.v[0]*b.v[2]+a.v[1]*b.v[5]+a.v[2]*b.v[8]
    }};
}

mat4 mat4_vec4_mul(mat4 a, vec4 b){
    return (mat4){{
        a.v[0]*b.v[0]+a.v[1]*b.v[4]+a.v[2]*b.v[8]+a.v[3]*b.v[12],
        a.v[0]*b.v[1]+a.v[1]*b.v[5]+a.v[2]*b.v[9]+a.v[3]*b.v[13],
        a.v[0]*b.v[2]+a.v[1]*b.v[6]+a.v[2]*b.v[10]+a.v[3]*b.v[14],
        a.v[0]*b.v[3]+a.v[1]*b.v[7]+a.v[2]*b.v[11]+a.v[3]*b.v[15]
    }};
}
