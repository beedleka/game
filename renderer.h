#include "types.h"
#include "math.h"
#include "opengl.h"
#include "fast_obj.h" // @Note replace this with mesh.h

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

typedef struct Shader{
    u32 shader_program;
    u32 mvp_location; // @Note we need a generalized way to store shader uniforms, hashmap maybe?
} Shader;

typedef struct Renderable{
    Transform transform;
    fastObjMesh* mesh;
    Shader shader;
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
void init_shader(Shader* shader, char* vertex_shader_filename, char* fragment_shader_filename);
void renderer_update();
void init_renderable(Renderable* renderable, fastObjMesh* mesh, Shader shader);
void init_camera(Camera* camera, Vec3 position, f32 field_of_view, f32 near_plane,
                f32 far_plane,
                Vec4 clear_color);
void renderer_close();