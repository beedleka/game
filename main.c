#include "window.h"
#include "time.h"
#include "types.h"
#include "utils.h"
#include "math.h"
#include "renderer.h"

#include <stdio.h>
#include <assert.h>

void resize_callback(){
    renderer_set_viewport(0, 0, current_window_size.width, current_window_size.height);
}

int confine_cursor = 0;

void input_callback(uint keycode, KeyState key_state){
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

Renderable cube2; // @Remove

void handle_input(f32 delta_time){
    if(keyboard[KEY_D] == PRESSED){
        cube2.transform.rotation.y += delta_time;
    }
    if(keyboard[KEY_A] == PRESSED){
        cube2.transform.rotation.y -= delta_time;
    }

    if(keyboard[KEY_W] == PRESSED){
        cube2.transform.rotation.x += delta_time;
    }
    if(keyboard[KEY_S] == PRESSED){
        cube2.transform.rotation.x -= delta_time;
    }

    if(keyboard[KEY_Q] == PRESSED){
        cube2.transform.rotation.z += delta_time;
    }
    if(keyboard[KEY_E] == PRESSED){
        cube2.transform.rotation.z -= delta_time;
    }
}

f32 cube_vertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f,
 0.5f,  0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, -0.5f, 0.0f,
 0.5f,  0.5f, -0.5f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f,
-0.5f,  0.5f, -0.5f, 0.0f,

-0.5f, -0.5f,  0.5f, 1.0f,
 0.5f, -0.5f,  0.5f, 1.0f,
 0.5f,  0.5f,  0.5f, 1.0f,
 0.5f,  0.5f,  0.5f, 1.0f,
-0.5f,  0.5f,  0.5f, 1.0f,
-0.5f, -0.5f,  0.5f, 1.0f,

-0.5f,  0.5f,  0.5f, 2.0f,
-0.5f,  0.5f, -0.5f, 2.0f,
-0.5f, -0.5f, -0.5f, 2.0f,
-0.5f, -0.5f, -0.5f, 2.0f,
-0.5f, -0.5f,  0.5f, 2.0f,
-0.5f,  0.5f,  0.5f, 2.0f,

 0.5f,  0.5f,  0.5f, 3.0f,
 0.5f, -0.5f, -0.5f, 3.0f,
 0.5f,  0.5f, -0.5f, 3.0f,
 0.5f, -0.5f, -0.5f, 3.0f,
 0.5f,  0.5f,  0.5f, 3.0f,
 0.5f, -0.5f,  0.5f, 3.0f,

-0.5f, -0.5f, -0.5f, 4.0f,
 0.5f, -0.5f, -0.5f, 4.0f,
 0.5f, -0.5f,  0.5f, 4.0f,
 0.5f, -0.5f,  0.5f, 4.0f,
-0.5f, -0.5f,  0.5f, 4.0f,
-0.5f, -0.5f, -0.5f, 4.0f,

-0.5f,  0.5f, -0.5f, 5.0f,
 0.5f,  0.5f,  0.5f, 5.0f,
 0.5f,  0.5f, -0.5f, 5.0f,
 0.5f,  0.5f,  0.5f, 5.0f,
-0.5f,  0.5f, -0.5f, 5.0f,
-0.5f,  0.5f,  0.5f, 5.0f,
};

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
    window_set_input_callback(input_callback);

    Camera main_camera;
    init_camera(&main_camera, (Vec3){0, 0, 0}, (Vec3){0, 0, 0}, 45, 0.1, 1000,
                (Vec4){1, 1, 1, 1});

    Shader shader;
    init_shader(&shader, "shaders/test_vertex.glsl", "shaders/test_fragment.glsl");

    init_renderable(&cube2, cube_vertices, sizeof(cube_vertices)/sizeof(f32), shader);
    cube2.transform.position = (Vec3){0, 0, -3};
    cube2.transform.rotation = (Quaternion){0, 0, 0, 1};
    cube2.transform.scale = (Vec3){1, 1, 1};

    u64 last_time = get_time()-10000;

    f32 x = 0;

    while(1){
        u64 current_time = get_time();
        f32 delta_time = ((f32)(current_time-last_time))/1000000;
        last_time = current_time;

        // cube2.transform.rotation = quat_quat_mul(euler_to_quat((Vec3){0, x, 0}), quat_id());
        cube2.transform.rotation.y += delta_time/3;
        cube2.transform.rotation = quat_normalize(cube2.transform.rotation);
        x += delta_time;

        handle_input(delta_time);
        if(!window_event()) break;
        renderer_update(main_camera);
        if(confine_cursor) window_set_cursor_to_center();
    }

    return 0;
}