#include "window.h"
#include "time.h"
#include "types.h"
#include "utils.h"
#include "math.h"
#include "renderer.h"
#include "hashtable.h"
#include "image.h"

#include <stdio.h>
#include <math.h>

void resize_callback(){
    renderer_set_viewport(0, 0, current_window_size.width, current_window_size.height);
}

void keyboard_callback(u32 keycode, KeyState key_state){
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

f32 mouse_sensitivity = 0.002;
void mouse_callback(MousePos mouse_pos){
    main_camera.rotation.x -= mouse_pos.x*mouse_sensitivity;
    main_camera.rotation.y -= mouse_pos.y*mouse_sensitivity;
    if(main_camera.rotation.y > rad(89.0)){
        main_camera.rotation.y = rad(89.0);
    }
    if(main_camera.rotation.y < -rad(89.0)){
        main_camera.rotation.y = -rad(89.0);
    }
}

Camera main_camera;

int fly = 1;
void handle_input(f32 delta_time){
    f32 speed = 4;
    Vec3 forward;
    f32 x = main_camera.rotation.x;
    f32 y = main_camera.rotation.y;
    forward.x = cos(x)*cos(y);
    if(fly){
        forward.y = sin(y);
    }
    else{
        forward.y = 0;
    }
    forward.z = sin(x)*cos(y);
    forward = vec3_normalize(forward);
    Vec3 right = vec3_normalize(vec3_cross(forward, (Vec3){0.0, 1.0, 0.0}));
    f32 x_move = 0;
    f32 z_move = 0;
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

i32 main(){
    u8 err = window_create("game", 800, 600);
    if(err){
        return 1;
    }

    err = renderer_init();
    if(err){
        return 1;
    }
    renderer_set_swap_interval(1);
    confine_cursor_to_center = 0;

    window_set_resize_callback(resize_callback);
    window_set_keyboard_callback(keyboard_callback);
    window_set_mouse_callback(mouse_callback);

    init_camera(&main_camera, (Vec3){0, 1, -5}, 90, 0.1, 10000,
                (Vec4){1, 1, 1, 1});

    Mesh* cube_mesh = mesh_from_obj("models/cube.obj");
    Mesh* plane_mesh = mesh_from_obj("models/plane.obj");

    Texture* texture = init_texture("textures/texture.tex", WRAP_REPEAT,
                        FILTER_LINEAR, FILTER_LINEAR);

    Shader* plain_shader = init_shader("shaders/plain_vertex.glsl", "shaders/plain_fragment.glsl");

    Material* simple_material1 = init_material(plain_shader);
    simple_material1->texture = texture;
    Material* simple_material2 = init_material(plain_shader);

    Renderable* cube = init_renderable(cube_mesh, simple_material1);
    cube->transform.position = (Vec3){0, 1, 0};
    Renderable* ground = init_renderable(plane_mesh, simple_material2);
    ground->enable_face_culling = 0;
    ground->rasterization_mode = RASTERIZATION_WIREFRAME;

    Vec3 v1 = (Vec3){1, 0, 0};
    material_set_uniform(simple_material1, "color", &v1.v);
    Vec3 v2 = (Vec3){0, 0, 0};
    material_set_uniform(simple_material2, "color", &v2.v);

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