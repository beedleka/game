#pragma once

#include "types.h"
#include "math.h"
#include "opengl.h"
#include "fast_obj.h" // @Note replace this with mesh.h
#include "hashtable.h"

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

typedef enum{
    SOLID,
    WIREFRAME
} RasterizationMode;

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
} Material;

typedef struct Renderable{
    int id;
    Transform transform;
    fastObjMesh* mesh;
    Material* material;
    u32 vertex_array_object;
    RasterizationMode rasterization_mode;
    int enable_face_culling;
} Renderable;

#define MAX_RENDERABLES 100

extern Camera main_camera;

int renderer_init();
void renderer_set_viewport(int x, int y, int width, int height);
void renderer_set_swap_interval(int interval);
void renderer_clear(Vec4 clear_color);
void renderer_swap_buffers();
void renderer_update();
Renderable* init_renderable(fastObjMesh* mesh, Material* material);
void free_renderable(Renderable* renderable);
Material* init_material(Shader* shader);
void free_material(Material* material);
Shader* init_shader(const char* vertex_shader_filename, const char* fragment_shader_filename);
void free_shader(Shader* shader);
void init_camera(Camera* camera, Vec3 position, f32 field_of_view, f32 near_plane,
                f32 far_plane,
                Vec4 clear_color);
void renderer_close();
void material_set_uniform(Material* material, const char* name, void* value);
void shader_upload_uniform(Uniform* uniform, void* value);