#include "renderer.h"

Renderable** renderables;
int living_renderables = 0;

int renderer_init(){
    renderables = malloc(MAX_RENDERABLES*sizeof(Renderable));
    return opengl_init(3, 3);
}

void renderer_set_viewport(int x, int y, int width, int height){
    glViewport(x, y, width, height);
}

void renderer_set_swap_interval(int interval){
    opengl_set_swap_interval(interval);
}

void renderer_clear(Vec4 clear_color){
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_swap_buffers(){
    opengl_swap_buffers();
}

u32 renderer_load_shader(const char* vertex_shader_filename, const char* fragment_shader_filename){
    return opengl_load_shader(vertex_shader_filename, fragment_shader_filename);
}

void renderer_update(){
    for(int i = 0; i < living_renderables; i++){
        glUseProgram(renderables[i]->shader_program);
        glBindVertexArray(renderables[i]->vertex_array_object);

        Mat4 m = Mat4_id();
        Mat4 v = Mat4_id();
        Mat4 p = Mat4_id();
        m = Mat4_Mat4_mul(scale_3d(renderables[i]->transform.scale), m);
        // m = Mat4_Mat4_mul(rotate_3d(renderables[i]->transform->rotation, m);
        m = Mat4_Mat4_mul(translate_3d(renderables[i]->transform.position), m);

        p = perspective_projection(rad(45), (f32)current_window_size.width/(f32)current_window_size.height,
                                    0.1, 100);

        Mat4 mvp = Mat4_id();
        mvp = Mat4_Mat4_mul(m, Mat4_Mat4_mul(p, v));

        glUniformMatrix4fv(renderables[i]->mvp_location, 1, GL_FALSE, mvp.v);

        switch(renderables[i]->rasterization_mode){
            case SOLID:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            case WIREFRAME:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
        }

        glDrawArrays(GL_TRIANGLES, 0, renderables[i]->vertex_count);
    }
}

void init_renderable(Renderable* renderable, f32* vertex_buffer, u32 vertex_count, u32 shader_program){
    if(living_renderables == MAX_RENDERABLES){
        error("[ERROR] Maximum renderables reached");
        return;
    }

    u32 vbo, vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count*sizeof(f32), vertex_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glUseProgram(shader_program);

    renderable->vertex_count = vertex_count;
    renderable->mvp_location = glGetUniformLocation(shader_program, "mvp");
    renderable->vertex_buffer = vertex_buffer;
    renderable->vertex_array_object = vao;
    renderable->shader_program = shader_program;
    renderable->rasterization_mode = SOLID;

    renderable->transform.position = (Vec3){0, 0, -3};
    renderable->transform.scale = (Vec3){1, 1, 1};
    renderable->transform.rotation = (Vec3){0, 0, 0};

    renderables[living_renderables] = renderable;
    living_renderables++;
}

void renderer_close(){
    living_renderables = 0;
    if(renderables != NULL) free(renderables);
}