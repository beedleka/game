#include "renderer.h"

Renderable** renderables;
int living_renderables = 0;

int renderer_init(){
    renderables = malloc(MAX_RENDERABLES*sizeof(Renderable));
    return opengl_init(3, 3);
}

void renderer_set_viewport(int x, int y, int width, int height){
    opengl_set_viewport(x, y, width, height);
}

void renderer_set_swap_interval(int interval){
    opengl_set_swap_interval(interval);
}

void renderer_clear(Vec4 clear_color){
    opengl_clear(clear_color);
}

void renderer_swap_buffers(){
    opengl_swap_buffers();
}

void renderer_update(Camera* camera){
    renderer_clear(camera->clear_color);
    glEnable(GL_DEPTH_TEST);

    Mat4 p = mat4_id();
    p = perspective_projection_matrix(rad(camera->field_of_view),
                                (f32)current_window_size.width/(f32)current_window_size.height,
                                camera->near_plane, camera->far_plane);

    Mat4 v = mat4_id();
    v = mat4_mat4_mul(translate_3d_matrix(camera->position), v);

    for(int i = 0; i < living_renderables; i++){
        glUseProgram(renderables[i]->shader.shader_program);
        glBindVertexArray(renderables[i]->vertex_array_object);

        Mat4 m = mat4_id();
        m = mat4_mat4_mul(translate_3d_matrix(renderables[i]->transform.position), m);
        m = mat4_mat4_mul(rotate_3d_matrix(renderables[i]->transform.rotation), m);
        m = mat4_mat4_mul(scale_3d_matrix(renderables[i]->transform.scale), m);

        Mat4 mvp = mat4_id();
        mvp = mat4_mat4_mul(m, mat4_mat4_mul(v, p));

        glUniformMatrix4fv(renderables[i]->shader.mvp_location, 1, GL_FALSE, mvp.m);

        if(renderables[i]->enable_face_culling){
            glEnable(GL_CULL_FACE);
        }
        else{
            glDisable(GL_CULL_FACE);
        }

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

    renderer_swap_buffers();
}

void init_renderable(Renderable* renderable, f32* vertex_buffer, u32 vertex_count, Shader shader){
    if(living_renderables == MAX_RENDERABLES){
        error("Maximum renderables reached");
        return;
    }

    u32 vbo, vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count*sizeof(f32), vertex_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4*sizeof(f32), (void*)(3*sizeof(f32)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    renderable->vertex_count = vertex_count;
    renderable->vertex_buffer = vertex_buffer;
    renderable->vertex_array_object = vao;
    renderable->shader = shader;
    renderable->rasterization_mode = SOLID;
    renderable->transform.position = (Vec3){0, 0, 0};
    renderable->transform.scale = (Vec3){1, 1, 1};
    renderable->transform.rotation = quat_id();
    renderable->enable_face_culling = 1;

    renderables[living_renderables] = renderable;
    living_renderables++;
}

void init_shader(Shader* shader, const char* vertex_shader_filename, const char* fragment_shader_filename){
    u32 shader_program = opengl_load_shader(vertex_shader_filename, fragment_shader_filename);
    if(shader_program != 0){
        shader->shader_program = shader_program;
        glUseProgram(shader_program);
        shader->mvp_location = glGetUniformLocation(shader_program, "mvp");
    }
}

void init_camera(Camera* camera, Vec3 position, Quaternion rotation, f32 field_of_view, f32 near_plane,
                f32 far_plane,
                Vec4 clear_color){
    camera->position = position;
    camera->rotation = rotation;
    camera->field_of_view = field_of_view;
    camera->near_plane = near_plane;
    camera->far_plane = far_plane;
    camera->clear_color = clear_color;
}

void renderer_close(){
    living_renderables = 0;
    if(renderables != NULL) free(renderables);
}