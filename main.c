#include "window.h"
#include "time.h"
#include "utils.h"
#include "opengl.h"
#include "math.h"

int main(){
    int width = 800;
    int height = 600;

    int err = create_window("game", width, height);
    if(err){
        return 1;
    }

    init_opengl_context();
    load_opengl_functions();

    wglSwapInterval(1);

    uint16 shader_program = load_shader("shaders/test_vertex.glsl", "shaders/test_fragment.glsl");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    uint16 VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glEnable(1);

    int running = 1;

    int fps_size = 200;
    int average_fps_array[fps_size];
    for(int i = 0; i < fps_size; i++){
        average_fps_array[i] = -1;
    }
    int current_fps_pointer = 0;

    while(running){
        uint64 start = get_time();
        running = event_loop();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shader_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SwapBuffers(device_context);

        uint64 elapsed = (get_time()-start)/1000;
        int current_fps = (int)(1000/(elapsed == 0 ? 1 : elapsed));
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