#include "types.h"
#include "math.h"
#include "opengl.h"

typedef struct Transform{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
} Transform;

typedef enum{
    SOLID,
    WIREFRAME
} RasterizationMode;

typedef struct Renderable{
    Transform transform;
    f32* vertex_buffer;
    u32 vertex_count;
    u32 shader_program;
    u32 mvp_location; // @Note we need a generalized way to store shader uniforms
    u32 vertex_array_object;
    RasterizationMode rasterization_mode;
} Renderable;

#define MAX_RENDERABLES 100

int renderer_init();
void renderer_set_viewport(int x, int y, int width, int height);
void renderer_set_swap_interval(int interval);
void renderer_clear(Vec4 clear_color);
void renderer_swap_buffers();
u32 renderer_load_shader(const char* vertex_shader_filename, const char* fragment_shader_filename);
void renderer_update();
void init_renderable(Renderable* renderable, f32* vertex_buffer, u32 vertex_count, u32 shader_program);
void renderer_close();