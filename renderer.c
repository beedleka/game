#include "renderer.h"
#include "hashtable.h"
#include "opengl.h"
#include <stdio.h>

Renderable** renderables;
int living_renderables = 0;

int renderer_init(){
    renderables = calloc(MAX_RENDERABLES, sizeof(Renderable));
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mat4 p = mat4_id();
    p = perspective_projection_matrix(rad(camera->field_of_view),
                                (f32)current_window_size.width/(f32)current_window_size.height,
                                camera->near_plane, camera->far_plane);

    Vec3 forward;
    float x = camera->rotation.x;
    float y = camera->rotation.y;
    forward.x = cos(x)*cos(y);
    forward.y = sin(y);
    forward.z = sin(x)*cos(y);
    Mat4 v = lookat_matrix(camera->position, vec3_add(camera->position, forward), (Vec3){0, 1, 0});

    for(int i = 0; i < living_renderables; i++){
        glBindVertexArray(renderables[i]->vertex_array_object);

        Mat4 m = mat4_id();
        m = mat4_mat4_mul(translate_3d_matrix(renderables[i]->transform.position), m);
        m = mat4_mat4_mul(rotate_3d_matrix(renderables[i]->transform.rotation), m);
        m = mat4_mat4_mul(scale_3d_matrix(renderables[i]->transform.scale), m);

        Mat4 mvp = mat4_id();
        mvp = mat4_mat4_mul(m, mat4_mat4_mul(v, p));

        material_set_uniform(renderables[i]->material, "mvp", &mvp.m);

        // @Note Use uniform buffer object to upload in bulk
        Shader* curr_shader = renderables[i]->material->shader;
        glUseProgram(curr_shader->program);
        Hti it = ht_iter(renderables[i]->material->uniforms_values);
        while(ht_next(&it)){
            shader_upload_uniform(ht_get(curr_shader->uniforms, it.key), it.value);
        }

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

        glDrawElements(GL_TRIANGLES, renderables[i]->mesh->face_count*3, GL_UNSIGNED_INT, 0);
    }

    renderer_swap_buffers();
}

void material_set_uniform(Material* material, const char* name, void* value){
    ht_set(material->uniforms_values, name, value);
}

void shader_upload_uniform(Uniform* uniform, void* value){
    switch(uniform->type){
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(uniform->location, 1, GL_FALSE, value);
            break;
        case GL_FLOAT_VEC3:
            glUniform3fv(uniform->location, 1, value);
            break;
        default:
            error("Unknown uniform type");
    }
}

Renderable* init_renderable(fastObjMesh* mesh, Material* material){
    Renderable* renderable = malloc(sizeof(Renderable));
    if(living_renderables == MAX_RENDERABLES){
        error("Maximum renderables reached");
        return NULL;
    }

    u32 vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, mesh->position_count*sizeof(f32)*3, mesh->positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    int indices_size = mesh->face_count*3*sizeof(unsigned int);
    unsigned int* indices = malloc(indices_size);
    for(unsigned int i = 0; i < mesh->face_count; i++){
        indices[(i*3)] = mesh->indices[(i*3)].p;
        indices[(i*3)+1] = mesh->indices[(i*3)+1].p;
        indices[(i*3)+2] = mesh->indices[(i*3)+2].p;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
    free(indices);

    glBindVertexArray(0);

    renderable->mesh = mesh;
    renderable->vertex_array_object = vao;
    renderable->material = material;
    renderable->rasterization_mode = SOLID;
    renderable->transform.position = (Vec3){0, 0, 0};
    renderable->transform.scale = (Vec3){1, 1, 1};
    renderable->transform.rotation = quat_id();
    renderable->enable_face_culling = 1;
    renderable->id = living_renderables;

    renderables[living_renderables] = renderable;
    living_renderables++;
    return renderable;
}

void free_renderable(Renderable* renderable){
    if(living_renderables > 1){
        renderables[renderable->id] = renderables[living_renderables-1];
        renderables[renderable->id]->id = renderable->id;
        renderables[living_renderables-1] = NULL;
    }
    free(renderable);
    living_renderables--;
}

Material* init_material(Shader* shader){
    Material* material = malloc(sizeof(Material));
    material->shader = shader;
    material->uniforms_values = ht_create();
    return material;
}

void free_material(Material* material){
    ht_destroy(material->uniforms_values);
    free(material);
}

Shader* init_shader(const char* vertex_shader_filename, const char* fragment_shader_filename){
    Shader* shader = malloc(sizeof(Shader));
    u32 program = opengl_load_shader(vertex_shader_filename, fragment_shader_filename);
    if(program != 0){
        shader->program = program;
        glUseProgram(program);

        shader->uniforms = ht_create();

        int uniform_count;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniform_count);
        GLint uniform_size;
        GLenum uniform_type;
        const GLsizei buffer_size = 256;
        GLchar uniform_name[256];
        for(int i = 0; i < uniform_count; i++){
            glGetActiveUniform(program, (GLuint)i, buffer_size, NULL, &uniform_size, &uniform_type, uniform_name);
            Uniform* uniform = malloc(sizeof(Uniform));
            uniform->location = glGetUniformLocation(program, uniform_name);
            uniform->type = uniform_type;
            ht_set(shader->uniforms, uniform_name, uniform);
        }
    }
    return shader;
}

void free_shader(Shader* shader){
    ht_destroy(shader->uniforms);
    glDeleteProgram(shader->program);
    free(shader);
}

void init_camera(Camera* camera, Vec3 position, f32 field_of_view, f32 near_plane,
                f32 far_plane,
                Vec4 clear_color){
    camera->position = position;
    camera->rotation = (Vec3){PI/2, 0, 0};
    camera->field_of_view = field_of_view;
    camera->near_plane = near_plane;
    camera->far_plane = far_plane;
    camera->clear_color = clear_color;
}

void renderer_close(){
    living_renderables = 0;
    if(renderables != NULL) free(renderables);
}