#include "opengl.h"
#include "utils.h"

#ifdef _WIN32

int init_opengl_context(){
    if(device_context == NULL){
        fprintf(stderr, "[ERROR] init_opengl_context: A window is needed for opengl context creation\n");
        return 1;
    }

    PIXELFORMATDESCRIPTOR pixel_format = {0};
    pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixel_format.nVersion = 1;
    pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixel_format.iPixelType = PFD_TYPE_RGBA;
    pixel_format.cColorBits = 32;
    pixel_format.cDepthBits = 24;
    pixel_format.cStencilBits = 8;
    int good_pixel_format_id = ChoosePixelFormat(device_context, &pixel_format);
    PIXELFORMATDESCRIPTOR good_pixel_format;
    DescribePixelFormat(device_context,
                        good_pixel_format_id,
                        sizeof(PIXELFORMATDESCRIPTOR),
                        &good_pixel_format);
    SetPixelFormat(device_context, good_pixel_format_id, &good_pixel_format);

    HGLRC opengl_context = wglCreateContext(device_context);
    wglMakeCurrent(device_context, opengl_context);
    return 0;
}

int load_opengl_functions(){
    if(wglGetCurrentContext() == NULL){
        fprintf(stderr, "[ERROR] load_opengl_functions: An opengl context is needed to load opengl functions\n");
        return 1;
    }
    wglSwapInterval = wglGetProcAddress("wglSwapIntervalEXT");
    glCreateShader = wglGetProcAddress("glCreateShader");
    glShaderSource = wglGetProcAddress("glShaderSource");
    glCompileShader = wglGetProcAddress("glCompileShader");
    glGetShaderiv = wglGetProcAddress("glGetShaderiv");
    glDeleteShader = wglGetProcAddress("glDeleteShader");
    glGetShaderInfoLog = wglGetProcAddress("glGetShaderInfoLog");
    glCreateProgram = wglGetProcAddress("glCreateProgram");
    glAttachShader = wglGetProcAddress("glAttachShader");
    glLinkProgram = wglGetProcAddress("glLinkProgram");
    glGetProgramiv = wglGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = wglGetProcAddress("glGetProgramInfoLog");
    glDeleteProgram = wglGetProcAddress("glDeleteProgram");
    glGenBuffers = wglGetProcAddress("glGenBuffers");
    glBindBuffer = wglGetProcAddress("glBindBuffer");
    glBufferData = wglGetProcAddress("glBufferData");
    glVertexAttribPointer = wglGetProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = wglGetProcAddress("glEnableVertexAttribArray");
    glUseProgram = wglGetProcAddress("glUseProgram");
    glGenVertexArrays = wglGetProcAddress("glGenVertexArrays");
    glBindVertexArray = wglGetProcAddress("glBindVertexArray");
    return 0;
}

uint16 load_shader(const char* vertex_shader_filename, const char* fragment_shader_filename){
    FILE* vertex_shader_file = fopen(vertex_shader_filename, "rb");
    FILE* fragment_shader_file = fopen(fragment_shader_filename, "rb");

    if(vertex_shader_file == NULL){
        fprintf(stderr, "[ERROR] load_shader: no such file or directory \"%s\"\n", vertex_shader_filename);
        return 0;
    }

    if(fragment_shader_file == NULL){
        fprintf(stderr, "[ERROR] load_shader: no such file or directory \"%s\"\n", fragment_shader_filename);
        return 0;
    }

    int success;
    const char info[512];

    char* vertex_shader_text;
    load_file_to_buffer(vertex_shader_file, &vertex_shader_text);
    fclose(vertex_shader_file);
    uint16 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    free(vertex_shader_text);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info);
        fprintf(stderr, "[ERROR] load_shader: Failed to compile vertex shader:\n%s", info);
        glDeleteShader(vertex_shader);
        return 0;
    }

    char* fragment_shader_text;
    load_file_to_buffer(fragment_shader_file, &fragment_shader_text);
    fclose(fragment_shader_file);
    uint16 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    free(fragment_shader_text);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, info);
        fprintf(stderr, "[ERROR] load_shader: Failed to compile fragment shader:\n%s", info);
        glDeleteShader(fragment_shader);
        return 0;
    }

    uint16 shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader_program, 512, NULL, info);
        glDeleteProgram(shader_program);
        fprintf(stderr, "[ERROR] load_shader: Failed to link shader program:\n%s", info);
        return 0;
    }

    return shader_program;
}

#endif