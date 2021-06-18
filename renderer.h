#pragma once

#include "types.h"
#include "math.h"
#include "opengl.h"
#include "fast_obj.h" // @Note replace this with mesh.h
#include "stb_image.h" // @Note replace this with image.h
#include "hashtable.h"

#define RASTERIZATION_SOLID GL_FILL
#define RASTERIZATION_WIREFRAME GL_LINE

#define WRAP_REPEAT GL_REPEAT
#define WRAP_MIRRORED_REPEAT GL_MIRRORED_REPEAT
#define WRAP_CLAMP_EDGE GL_CLAMP_TO_EDGE
#define WRAP_CLAMP_BORDER GL_CLAMP_TO_BORDER

#define FILTER_NEAREST GL_NEAREST
#define FILTER_LINEAR GL_LINEAR

#define MAX_RENDERABLES 100

typedef struct Transform{
    Vec3 position;
    Quaternion rotation;
    Vec3 scale;
} Transform;

typedef struct Camera{
    Vec3 position;
    Vec3 rotation;
    f32 field_of_view;
    f32 near_plane;
    f32 far_plane;
    Vec4 clear_color;
} Camera;

typedef struct Mesh{
    int index_count;
    u32 vao;
    u32 vbo;
    u32 ebo;
} Mesh;

typedef struct Texture{
    int id;
} Texture;

typedef struct Uniform{
    u32 location;
    GLenum type;
} Uniform;

typedef struct Shader{
    u32 program;
    Ht* uniforms;
} Shader;

typedef struct Material{
    Shader* shader;
    Ht* uniforms_values;
    Texture* texture;
} Material;

typedef struct Renderable{
    int id;
    Transform transform;
    Mesh* mesh;
    Material* material;
    int rasterization_mode;
    int enable_face_culling;
} Renderable;

extern Camera main_camera;

int renderer_init();
void renderer_set_viewport(int x, int y, int width, int height);
void renderer_set_swap_interval(int interval);
void renderer_clear(Vec4 clear_color);
void renderer_swap_buffers();
void renderer_update();
Renderable* init_renderable(Mesh* mesh, Material* material);
void free_renderable(Renderable* renderable);
Material* init_material(Shader* shader);
void free_material(Material* material);
Shader* init_shader(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
void free_shader(Shader* shader);
Texture* init_texture(const char* image_filepath, int texture_wrapping_mode,
                    int texture_min_filtering_mode, int texture_mag_filtering_mode);
void free_texture(Texture* texture);
Mesh* init_mesh(const char* mesh_filepath);
void free_mesh(Mesh* mesh);
void init_camera(Camera* camera, Vec3 position, f32 field_of_view, f32 near_plane,
                f32 far_plane,
                Vec4 clear_color);
void renderer_close();
void material_set_uniform(Material* material, const char* name, void* value);
void shader_upload_uniform(Uniform* uniform, void* value);