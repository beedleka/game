#include "window.h"
#include "time.h"
#include "types.h"
#include "utils.h"
#include "math.h"
#include "renderer.h"
#include "mesh.h"
#include "fast_obj.h" // @Note replace this with mesh.h

#include <stdio.h>
#include <assert.h>

void resize_callback(){
    renderer_set_viewport(0, 0, current_window_size.width, current_window_size.height);
}

void keyboard_callback(uint keycode, KeyState key_state){
    if(keycode == KEY_ESCAPE && key_state == PRESSED){
        window_close();
    }
    if(keycode == KEY_F11 && key_state == PRESSED){
        if(current_window_state == WINDOWED){
            window_set_state(WINDOWED_FULLSCREEN);
        }
        else{
            window_set_state(WINDOWED);
        }
    }
    if(keycode == KEY_F1 && key_state == PRESSED){
        renderer_set_swap_interval(0);
    }
    if(keycode == KEY_F2 && key_state == PRESSED){
        renderer_set_swap_interval(1);
    }
}

float mouse_sensivity = 0.002;
void mouse_callback(MousePos mouse_pos){
    main_camera.rotation.x -= mouse_pos.x*mouse_sensivity;
    main_camera.rotation.y -= mouse_pos.y*mouse_sensivity;
    if(main_camera.rotation.y > rad(89.0)) {
        main_camera.rotation.y = rad(89.0);
    }
    if (main_camera.rotation.y < -rad(89.0)) {
        main_camera.rotation.y = -rad(89.0);
    }
}

Camera main_camera;

void print_vec3(Vec3 v){
    printf("%f %f %f\n", v.x, v.y, v.z);
}

void handle_input(f32 delta_time){
    f32 speed = 4;
    Vec3 forward;
    float x = main_camera.rotation.x;
    float y = main_camera.rotation.y;
    forward.x = cos(x)*cos(y);
    forward.y = 0;
    forward.z = sin(x)*cos(y);
    forward = vec3_normalize(forward);
    Vec3 right = vec3_normalize(vec3_cross(forward, (Vec3){0.0, 1.0, 0.0}));
    float x_move = 0;
    float z_move = 0;
    if(keyboard[KEY_D] == PRESSED){
        x_move -= 1;
    }
    if(keyboard[KEY_A] == PRESSED){
        x_move += 1;
    }
    if(keyboard[KEY_W] == PRESSED){
        z_move += 1;
    }
    if(keyboard[KEY_S] == PRESSED){
        z_move -= 1;
    }

    main_camera.position = vec3_add(main_camera.position, vec3_scale(vec3_normalize(vec3_add(
        vec3_scale(forward, z_move), vec3_scale(right, x_move))), speed*delta_time));
}

int main(){
    int err = window_create("game", 800, 600);
    if(err){
        return 1;
    }

    err = renderer_init();
    if(err){
        return 1;
    }
    renderer_set_swap_interval(1);

    window_set_resize_callback(resize_callback);
    window_set_keyboard_callback(keyboard_callback);
    window_set_mouse_callback(mouse_callback);

    init_camera(&main_camera, (Vec3){0, 1, -5}, 90, 0.1, 10000,
                (Vec4){1, 1, 1, 1});

    Shader plain_shader;
    init_shader(&plain_shader, "shaders/plain_vertex.glsl", "shaders/plain_fragment.glsl");

    fastObjMesh* sphere_mesh = fast_obj_read("models/sphere.obj");
    if(sphere_mesh == NULL){
        error("fast_obj_read: can't load model file `models/sphere.obj`");
        return 0;
    }
    fastObjMesh* plane_mesh = fast_obj_read("models/plane.obj");
    if(plane_mesh == NULL){
        error("fast_obj_read: can't load model file `models/plane.obj`");
        return 0;
    }

    Renderable sphere;
    init_renderable(&sphere, sphere_mesh, plain_shader);
    sphere.transform.position = (Vec3){0, 1, 0};
    Renderable ground;
    init_renderable(&ground, plane_mesh, plain_shader);
    ground.transform.scale = (Vec3){50, 1, 50};
    ground.enable_face_culling = 0;
    ground.rasterization_mode = WIREFRAME;

    u64 last_time = get_time()-10000;

    while(1){
        u64 current_time = get_time();
        f32 delta_time = ((f32)(current_time-last_time))/1000000;
        last_time = current_time;

        handle_input(delta_time);
        if(!window_event()) break;

        renderer_update(&main_camera);
    }

    return 0;
}