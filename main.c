#include "window.h"
#include "time.h"
#include "types.h"
#include "utils.h"
#include "opengl.h"
#include "math.h"

#include <stdio.h>
#include <assert.h>

void resize_callback(){
    glViewport(0, 0, current_window_size.width, current_window_size.height);
}

int main(){
    int err = create_window("game", 800, 600);
    if(err){
        return 1;
    }

    set_resize_callback(resize_callback);

    init_opengl(3, 3);

    set_swap_interval(1);

    u16 shader_program = load_shader("shaders/test_vertex.glsl", "shaders/test_fragment.glsl");

    f32 vertices[] = {
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

    u32 VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    int running = 1;

    #define fps_size 400
    int average_fps_array[fps_size];
    for(int i = 0; i < fps_size; i++){
        average_fps_array[i] = -1;
    }
    int current_fps_pointer = 0;


    glUseProgram(shader_program);
    int m_location = glGetUniformLocation(shader_program, "m");
    int v_location = glGetUniformLocation(shader_program, "v");
    int p_location = glGetUniformLocation(shader_program, "p");

    u64 last_time = get_time()-10000;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float rot = 0;
    while(1){
        u64 current_time = get_time();
        u64 delta_time = current_time-last_time;
        last_time = current_time;

        running = event_loop();
        if(!running) break;

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);

        glUseProgram(shader_program);
        mat4 m = mat4_id();
        mat4 v = mat4_id();
        mat4 p = mat4_id();
        m = mat4_mat4_mul(rotate_3d(rad(rot), (vec3){1, 0, 0}), m);
        rot += 0.9;
        v = mat4_mat4_mul(translate_3d(0, 0, -3), v);
        p = perspective_projection(rad(45), (f32)current_window_size.width/(f32)current_window_size.height,
                                    0.1, 1000);

        glUniformMatrix4fv(m_location, 1, GL_FALSE, m.v);
        glUniformMatrix4fv(v_location, 1, GL_FALSE, v.v);
        glUniformMatrix4fv(p_location, 1, GL_FALSE, p.v);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(float));
        swap_buffers();

        int current_fps = (int)(1000*1000/(delta_time == 0 ? 1 : delta_time));
        average_fps_array[current_fps_pointer] = current_fps;
        current_fps_pointer++;
        if(current_fps_pointer == fps_size-1) current_fps_pointer = 0;
        int average_fps = 0;
        int current_fps_size = 0;
        for(int i = 0; i < fps_size; i++){
            if(average_fps_array[i] == -1) continue;
            current_fps_size++;
            average_fps += average_fps_array[i];
        }
        average_fps /= current_fps_size;
        char fps[50];
        sprintf(fps, "%d fps\n", average_fps);
        set_window_title(fps);
    }

    return 0;
}