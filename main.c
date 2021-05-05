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

f32 cube_vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
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

    window_set_resize_callback(resize_callback);

    u32 shader = renderer_load_shader("shaders/test_vertex.glsl", "shaders/test_fragment.glsl");

    Renderable cube;
    init_renderable(&cube, cube_vertices, sizeof(cube_vertices)/sizeof(f32), shader);
    cube.rasterization_mode = WIREFRAME;
    cube.transform.position.x -= 0.7;

    Renderable cube2;
    init_renderable(&cube2, cube_vertices, sizeof(cube_vertices)/sizeof(f32), shader);
    cube2.transform.position.x += 0.7;

    renderer_set_swap_interval(1);

    u64 last_time = get_time()-10000;
    while(1){
        u64 current_time = get_time();
        u64 delta_time = current_time-last_time;
        last_time = current_time;
        int current_fps = (int)(1000*1000/(delta_time == 0 ? 1 : delta_time));
        char fps[50];
        // printf("%d fps\n", current_fps);

        cube.transform.position.x += 0.01;

        if(!window_event()) break;
        renderer_clear((Vec4){1.0f, 1.0f, 1.0f, 1.0f});
        renderer_update();
        renderer_swap_buffers();
    }

    return 0;
}