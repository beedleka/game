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

Mat4 mat4_mat4_add(Mat4 a, Mat4 b){
    return (Mat4){
        a.m[0]+b.m[0], a.m[1]+b.m[1], a.m[2]+b.m[2], a.m[3]+b.m[3],
        a.m[4]+b.m[4], a.m[5]+b.m[5], a.m[6]+b.m[6], a.m[7]+b.m[7],
        a.m[8]+b.m[8], a.m[9]+b.m[9], a.m[10]+b.m[10], a.m[11]+b.m[11],
        a.m[12]+b.m[12], a.m[13]+b.m[13], a.m[14]+b.m[14], a.m[15]+b.m[15]
    };
}

Mat4 mat4_mat4_mul(Mat4 a, Mat4 b){
    return (Mat4){
        a.m[0]*b.m[0]+a.m[1]*b.m[4]+a.m[2]*b.m[8]+a.m[3]*b.m[12],
        a.m[0]*b.m[1]+a.m[1]*b.m[5]+a.m[2]*b.m[9]+a.m[3]*b.m[13],
        a.m[0]*b.m[2]+a.m[1]*b.m[6]+a.m[2]*b.m[10]+a.m[3]*b.m[14],
        a.m[0]*b.m[3]+a.m[1]*b.m[7]+a.m[2]*b.m[11]+a.m[3]*b.m[15],

        a.m[4]*b.m[0]+a.m[5]*b.m[4]+a.m[6]*b.m[8]+a.m[7]*b.m[12],
        a.m[4]*b.m[1]+a.m[5]*b.m[5]+a.m[6]*b.m[9]+a.m[7]*b.m[13],
        a.m[4]*b.m[2]+a.m[5]*b.m[6]+a.m[6]*b.m[10]+a.m[7]*b.m[14],
        a.m[4]*b.m[3]+a.m[5]*b.m[7]+a.m[6]*b.m[11]+a.m[7]*b.m[15],

        a.m[8]*b.m[0]+a.m[9]*b.m[4]+a.m[10]*b.m[8]+a.m[11]*b.m[12],
        a.m[8]*b.m[1]+a.m[9]*b.m[5]+a.m[10]*b.m[9]+a.m[11]*b.m[13],
        a.m[8]*b.m[2]+a.m[9]*b.m[6]+a.m[10]*b.m[10]+a.m[11]*b.m[14],
        a.m[8]*b.m[3]+a.m[9]*b.m[7]+a.m[10]*b.m[11]+a.m[11]*b.m[15],

        a.m[12]*b.m[0]+a.m[13]*b.m[4]+a.m[14]*b.m[8]+a.m[15]*b.m[12],
        a.m[12]*b.m[1]+a.m[13]*b.m[5]+a.m[14]*b.m[9]+a.m[15]*b.m[13],
        a.m[12]*b.m[2]+a.m[13]*b.m[6]+a.m[14]*b.m[10]+a.m[15]*b.m[14],
        a.m[12]*b.m[3]+a.m[13]*b.m[7]+a.m[14]*b.m[11]+a.m[15]*b.m[15]
    };
}

Mat3 mat3_mat3_add(Mat3 a, Mat3 b){
    return (Mat3){
        a.m[0]+b.m[0], a.m[1]+b.m[1], a.m[2]+b.m[2],
        a.m[3]+b.m[3], a.m[4]+b.m[4], a.m[5]+b.m[5],
        a.m[6]+b.m[6], a.m[7]+b.m[7], a.m[8]+b.m[8]
    };
}

Mat3 mat3_mat3_mul(Mat3 a, Mat3 b){
    return (Mat3){
        a.m[0]*b.m[0]+a.m[1]*b.m[3]+a.m[2]*b.m[6],
        a.m[0]*b.m[1]+a.m[1]*b.m[4]+a.m[2]*b.m[7],
        a.m[0]*b.m[2]+a.m[1]*b.m[5]+a.m[2]*b.m[8],

        a.m[3]*b.m[0]+a.m[4]*b.m[3]+a.m[5]*b.m[6],
        a.m[3]*b.m[1]+a.m[4]*b.m[4]+a.m[5]*b.m[7],
        a.m[3]*b.m[2]+a.m[4]*b.m[5]+a.m[5]*b.m[8],

        a.m[6]*b.m[0]+a.m[7]*b.m[3]+a.m[8]*b.m[6],
        a.m[6]*b.m[1]+a.m[7]*b.m[4]+a.m[8]*b.m[7],
        a.m[6]*b.m[2]+a.m[7]*b.m[5]+a.m[8]*b.m[8]
    };
}

Vec3 mat3_vec3_mul(Mat3 a, Vec3 b){
    return (Vec3){
        b.v[0]*a.m[0]+b.v[1]*a.m[3]+b.v[2]*a.m[6],
        b.v[0]*a.m[1]+b.v[1]*a.m[4]+b.v[2]*a.m[7],
        b.v[0]*a.m[2]+b.v[1]*a.m[5]+b.v[2]*a.m[8]
    };
}

Vec4 mat4_vec4_mul(Mat4 a, Vec4 b){
    return (Vec4){
        b.v[0]*a.m[0]+b.v[1]*a.m[4]+b.v[2]*a.m[8]+b.v[3]*a.m[12],
        b.v[0]*a.m[1]+b.v[1]*a.m[5]+b.v[2]*a.m[9]+b.v[3]*a.m[13],
        b.v[0]*a.m[2]+b.v[1]*a.m[6]+b.v[2]*a.m[10]+b.v[3]*a.m[14],
        b.v[0]*a.m[3]+b.v[1]*a.m[7]+b.v[2]*a.m[11]+b.v[3]*a.m[15]
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

Mat4 lookat_matrix(Vec3 camera_pos, Vec3 target_pos, Vec3 world_up){
    Vec3 camera_direction = vec3_normalize(vec3_sub(target_pos, camera_pos));
    Vec3 camera_right = vec3_normalize(vec3_cross(world_up, camera_direction));
    Vec3 camera_up = vec3_cross(camera_direction, camera_right);
    camera_direction = vec3_scale(camera_direction, -1);
    return (Mat4){
        camera_right.x, camera_up.x, camera_direction.x, 0,
        camera_right.y, camera_up.y, camera_direction.y, 0,
        camera_right.z, camera_up.z, camera_direction.z, 0,
        -vec3_dot(camera_right, camera_pos),
        -vec3_dot(camera_up, camera_pos),
        -vec3_dot(camera_direction, camera_pos), 1
    };
}

f32 rad(f32 deg){
    return deg*PI/180;
}

f32 vec2_magnitude(Vec2 v){
    return sqrt(v.x*v.x + v.y*v.y);
}

Vec2 vec2_normalize(Vec2 v){
    f32 m = vec2_magnitude(v);
    if(m == 0) return (Vec2){0, 0};
    return (Vec2){
        v.x/m,
        v.y/m
    };
}

Vec2 vec2_add(Vec2 a, Vec2 b){
    return (Vec2){
        a.x+b.x,
        a.y+b.y
    };
}

Vec2 vec2_sub(Vec2 a, Vec2 b){
    return (Vec2){
        a.x-b.x,
        a.y-b.y
    };
}

Vec2 vec2_scale(Vec2 v, f32 s){
    return (Vec2){
        v.x*s,
        v.y*s
    };
}

f32 vec2_dot(Vec2 a, Vec2 b){
    return a.x*b.x + a.y*b.y;
}

Vec2 vec2_lerp(Vec2 a, Vec2 b, f32 t){
    t = t < 0 ? 0 : t;
    t = t > 1 ? 1 : t;
    return vec2_add(vec2_scale(a, t), vec2_scale(b, 1-t));
}

Vec3 vec3_cross(Vec3 a, Vec3 b){
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

f32 vec3_dot(Vec3 a, Vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3 vec3_normalize(Vec3 v){
    f32 m = vec3_magnitude(v);
    if(m == 0) return (Vec3){0, 0, 0};
    return (Vec3){
        v.x/m,
        v.y/m,
        v.z/m
    };
}

Vec3 vec3_add(Vec3 a, Vec3 b){
    return (Vec3){
        a.x+b.x,
        a.y+b.y,
        a.z+b.z,
    };
}

Vec3 vec3_sub(Vec3 a, Vec3 b){
    return (Vec3){
        a.x-b.x,
        a.y-b.y,
        a.z-b.z,
    };
}

Vec3 vec3_scale(Vec3 v, f32 s){
    return (Vec3){
        v.x*s,
        v.y*s,
        v.z*s,
    };
}

Vec3 vec3_lerp(Vec3 a, Vec3 b, f32 t){
    t = t < 0 ? 0 : t;
    t = t > 1 ? 1 : t;
    return vec3_add(vec3_scale(a, t), vec3_scale(b, 1-t));
}

Vec4 vec4_normalize(Vec4 v){
    f32 m = vec4_magnitude(v);
    if(m == 0) return (Vec4){0, 0, 0, 0};
    return (Vec4){
        v.x/m,
        v.y/m,
        v.z/m,
        v.w/m
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
        sx*cy*cz-cx*sy*sz,
        cx*sy*cz+sx*cy*sz,
        cx*cy*sz-sx*sy*cz,
        cx*cy*cz+sx*sy*sz
    };
}

Quaternion quat_mul(Quaternion a, Quaternion b){
    return (Quaternion){
        a.w*b.x+a.x*b.w+a.y*b.z-a.z*b.y,
        a.w*b.y-a.x*b.z+a.y*b.w+a.z*b.x,
        a.w*b.z+a.x*b.y-a.y*b.x+a.z*b.w,
        a.w*b.w-a.x*b.x-a.y*b.y-a.z*b.z
    };
}

Quaternion quat_id(){
    return (Quaternion){0, 0, 0, 1};
}

f32 quat_magnitude(Quaternion q){
    return sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

Quaternion quat_normalize(Quaternion q){
    f32 m = quat_magnitude(q);
    if(m == 0) return (Quaternion){0, 0, 0, 0};
    return (Quaternion){
        q.x/m,
        q.y/m,
        q.z/m,
        q.w/m
    };
}

Quaternion quat_conjugate(Quaternion q){
    return (Quaternion){-q.x, -q.y, -q.z, q.w};
}

Quaternion quat_inverse(Quaternion q){
    f32 m = quat_magnitude(q);
    if(m == 0) return (Quaternion){0, 0, 0, 0};
    m *= m;
    return (Quaternion){-q.x/m, -q.y/m, -q.z/m, q.w/m};
}

Quaternion quat_difference(Quaternion a, Quaternion b){
    return quat_mul(quat_inverse(a), b);
}

Quaternion quat_exp(Quaternion q){
    Vec3 v = (Vec3){q.x, q.y, q.z};
    f32 v_m = vec3_magnitude(v);
    Vec3 v_n = vec3_normalize(v);
    f32 sin_v = sin(v_m);
    f32 exp_w = exp(q.w);
    return (Quaternion){
        v_n.x*sin_v*exp_w,
        v_n.y*sin_v*exp_w,
        v_n.z*sin_v*exp_w,
        cos(v_m)*exp_w
    };
}

Quaternion quat_log(Quaternion q){
    Vec3 v = (Vec3){q.x, q.y, q.z};
    Vec3 v_n = vec3_normalize(v);
    f32 m = quat_magnitude(q);
    f32 a = acos(q.w/m);
    return (Quaternion){
        v_n.x*a,
        v_n.y*a,
        v_n.z*a,
        log(m)
    };
}

Quaternion quat_scale(Quaternion q, f32 s){
    return (Quaternion){q.x*s, q.y*s, q.z*s, q.w*s};
}

Quaternion quat_pow(Quaternion q, f32 n){
    return quat_exp(quat_scale(quat_log(q), n));
}

Quaternion quat_slerp(Quaternion q1, Quaternion q2, f32 t){
    t = t < 0 ? 0 : t;
    t = t > 1 ? 1 : t;
    return quat_mul(q1, quat_pow(quat_mul(quat_inverse(q1), q2), t));
}

f32 quat_dot_product(Quaternion q1, Quaternion q2){
    return q1.x*q2.x+q1.y*q2.y+q1.z*q2.z+q1.w*q2.w;
}