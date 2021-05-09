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
    f32 speed = 2;
    speed *= delta_time;

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

    u32 shader = renderer_load_shader("shaders/test_vertex.glsl", "shaders/test_fragment.glsl");

    init_renderable(&cube2, cube_vertices, sizeof(cube_vertices)/sizeof(f32), shader);
    cube2.transform.position = (Vec3){0, 0, -3};

    u64 last_time = get_time()-10000;
    while(1){
        u64 current_time = get_time();
        f32 delta_time = ((f32)(current_time-last_time))/1000000;
        last_time = current_time;
        // int current_fps = (int)(1000*1000/(delta_time == 0 ? 1 : delta_time));
        // char fps[50];
        // printf("%d fps\n", current_fps);

        handle_input(delta_time);
        if(!window_event()) break;
        renderer_update();
    }

    return 0;
}