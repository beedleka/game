#include "renderer.h"

Renderable** renderables;
u32 living_renderables = 0;

u8 renderer_init(){
    renderables = calloc(MAX_RENDERABLES, sizeof(Renderable*));
    return opengl_init(3, 3, 2);
}

void renderer_set_viewport(u32 x, u32 y, u32 width, u32 height){
    opengl_set_viewport(x, y, width, height);
}

void renderer_set_swap_interval(u32 interval){
    opengl_set_swap_interval(interval);
}

void renderer_clear(RGBA clear_color){
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

    Mat4 p = perspective_projection_matrix(rad(camera->field_of_view),
                                (f32)current_window_size.width/(f32)current_window_size.height,
                                camera->near_plane, camera->far_plane);
    Vec3 forward;
    f32 x = camera->rotation.x;
    f32 y = camera->rotation.y;
    forward.x = cos(x)*cos(y);
    forward.y = sin(y);
    forward.z = sin(x)*cos(y);
    Mat4 v = lookat_matrix(camera->position, vec3_add(camera->position, forward), (Vec3){0, 1, 0});

    for(u32 i = 0; i < living_renderables; i++){
        if(renderables[i]->mesh == NULL) continue;
        if(renderables[i]->material == NULL) continue;

        glBindVertexArray(renderables[i]->mesh->vao);

        Mat4 m = mat4_id();
        m = mat4_mat4_mul(translate_3d_matrix(renderables[i]->transform.position), m);
        m = mat4_mat4_mul(rotate_3d_matrix(renderables[i]->transform.rotation), m);
        m = mat4_mat4_mul(scale_3d_matrix(renderables[i]->transform.scale), m);

        Mat4 mvp = mat4_id();
        mvp = mat4_mat4_mul(m, mat4_mat4_mul(v, p));

        material_set_uniform(renderables[i]->material, "mvp", &mvp.m);

        Shader* curr_shader = renderables[i]->material->shader;
        glUseProgram(curr_shader->program);

        // @Note Use uniform buffer object to upload in bulk
        Hti it = ht_iter(renderables[i]->material->uniforms_values);
        while(ht_next(&it)){
            Uniform* uniform = ht_get(curr_shader->uniforms, it.key);
            if(uniform != NULL) shader_upload_uniform(uniform, it.value);
        }

        if(renderables[i]->enable_face_culling){
            glEnable(GL_CULL_FACE);
        }
        else{
            glDisable(GL_CULL_FACE);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        if(renderables[i]->material->texture != NULL){
            glBindTexture(GL_TEXTURE_2D, renderables[i]->material->texture->id);
        }

        glPolygonMode(GL_FRONT_AND_BACK, renderables[i]->rasterization_mode);
        if(renderables[i]->mesh->draw_arrays){
            glDrawArrays(GL_LINES, 0, renderables[i]->mesh->draw_count);
        }
        else{
            glDrawElements(GL_TRIANGLES, renderables[i]->mesh->draw_count, GL_UNSIGNED_INT, 0);
        }
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

Renderable* init_renderable(Mesh* mesh, Material* material){
    if(living_renderables == MAX_RENDERABLES){
        error("init_renderable: Maximum renderables reached");
        return NULL;
    }
    Renderable* renderable = malloc(sizeof(Renderable));

    renderable->id = living_renderables;
    renderable->mesh = mesh;
    renderable->material = material;
    renderable->rasterization_mode = RASTERIZATION_SOLID;
    renderable->transform.position = (Vec3){0, 0, 0};
    renderable->transform.scale = (Vec3){1, 1, 1};
    renderable->transform.rotation = quat_id();
    renderable->enable_face_culling = 1;

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

Mesh* mesh_from_obj(const char* obj_filepath){
    fastObjMesh* obj = fast_obj_read(obj_filepath);
    if(obj == NULL){
        error("fast_obj_read: can't load model file %s`", obj_filepath);
        return 0;
    }

    Mesh* mesh = malloc(sizeof(Mesh));

    struct tmp_vertex{
        u32 index;
        Vec3 position;
        Vec3 normal;
        Vec2 texcoord;
    };

    u32 index_count = obj->face_count;
    u32* indices = malloc(3*index_count*sizeof(u32));

    Ht* tmp_vertices = ht_create();
    char buffer[256];
    u32 index_counter = 0;
    for(u32 i = 0; i < obj->face_count; i++){
        for(u32 j = 0; j < 3; j++){
            u32 position_index = obj->indices[i*3+j].p-1;
            u32 texcoord_index = obj->indices[i*3+j].t-1;
            u32 normal_index = obj->indices[i*3+j].n-1;
            sprintf(buffer, "%d/%d/%d",
                position_index,
                texcoord_index,
                normal_index);
            if(ht_get(tmp_vertices, buffer) == NULL){
                struct tmp_vertex* tmp = malloc(sizeof(struct tmp_vertex));
                tmp->position = (Vec3){obj->positions[position_index*3],
                    obj->positions[position_index*3+1],
                    obj->positions[position_index*3+2]};
                tmp->texcoord = (Vec2){obj->texcoords[texcoord_index*2],
                    obj->texcoords[texcoord_index*2+1]};
                tmp->normal = (Vec3){obj->normals[normal_index*3],
                    obj->normals[normal_index*3+1],
                    obj->normals[normal_index*3+2]};
                tmp->index = index_counter;
                indices[i*3+j] = index_counter;
                index_counter++;
                ht_set(tmp_vertices, buffer, tmp);
            }
            else{
                indices[i*3+j] = ((struct tmp_vertex*)(ht_get(tmp_vertices, buffer)))->index;
            }
        }
    }
    Hti it = ht_iter(tmp_vertices);
    u32 vertex_count = tmp_vertices->count;

    f32* vertices = malloc(vertex_count*sizeof(f32)*8);
    while(ht_next(&it)){
        struct tmp_vertex* tmp = (struct tmp_vertex*)it.value;
        vertices[tmp->index*8] = tmp->position.x;
        vertices[tmp->index*8+1] = tmp->position.y;
        vertices[tmp->index*8+2] = tmp->position.z;
        vertices[tmp->index*8+3] = tmp->normal.x;
        vertices[tmp->index*8+4] = tmp->normal.y;
        vertices[tmp->index*8+5] = tmp->normal.z;
        vertices[tmp->index*8+6] = tmp->texcoord.x;
        vertices[tmp->index*8+7] = tmp->texcoord.y;
        free(tmp);
    }
    ht_destroy(tmp_vertices);

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);
    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count*8*sizeof(f32), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*index_count*sizeof(u32), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(f32), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(f32), (void*)(3*sizeof(f32)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(f32), (void*)(6*sizeof(f32)));
    glBindVertexArray(0);

    mesh->draw_count = index_count*3;
    mesh->draw_arrays = 0;

    return mesh;
}

void free_mesh(Mesh* mesh){
    glDeleteBuffers(1, &mesh->ebo);
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    free(mesh);
}

Material* init_material(Shader* shader){
    Material* material = malloc(sizeof(Material));
    material->shader = shader;
    material->uniforms_values = ht_create();
    material->texture = NULL;
    return material;
}

void free_material(Material* material){
    ht_destroy(material->uniforms_values);
    free(material);
}

Shader* init_shader(const char* vertex_shader_filepath, const char* fragment_shader_filepath){
    Shader* shader = malloc(sizeof(Shader));
    u32 program = opengl_load_shader(vertex_shader_filepath, fragment_shader_filepath);
    if(program != 0){
        shader->program = program;
        glUseProgram(program);

        shader->uniforms = ht_create();

        i32 uniform_count;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniform_count);
        GLint uniform_size;
        GLenum uniform_type;
        const GLsizei buffer_size = 256;
        GLchar uniform_name[256];
        for(i32 i = 0; i < uniform_count; i++){
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

Texture* init_texture(const char* image_filepath, u32 texture_wrapping_mode,
                    u32 texture_min_filtering_mode, u32 texture_mag_filtering_mode){
    u32 width, height;
    u8 channels;
    u8* image_data = load_image(image_filepath, &width, &height, &channels);
    if(image_data == NULL){
        error("init_texture: Can't load image file `%s`", image_filepath);
        return NULL;
    }
    Texture* texture = malloc(sizeof(Texture));
    u32 texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrapping_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrapping_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_min_filtering_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filtering_mode);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    u32 texture_type;
    switch(channels){
        case 24:
            texture_type = GL_RGB;
            break;
        case 32:
            texture_type = GL_RGBA;
            break;
        default:
            error("init_texture: Unknown texture format");
            return NULL;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, texture_type, width, height,
                0, texture_type, GL_UNSIGNED_BYTE, image_data);
    free_image(image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    texture->id = texture_id;
    return texture;
}

void free_texture(Texture* texture){
    free(texture);
}

void init_camera(Camera* camera, Vec3 position, f32 field_of_view, f32 near_plane,
                f32 far_plane,
                RGBA clear_color){
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