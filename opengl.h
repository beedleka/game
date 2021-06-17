#pragma once

#include "types.h"
#include "utils.h"
#include "window.h"
#include "math.h"

#include <stdio.h>
#include <string.h>

typedef struct GLExtensions{
    int GL_ARB_compute_shader_available;
} GLExtensions;

int opengl_init(int opengl_major_version, int opengl_minor_version);
void opengl_swap_buffers();
u32 opengl_load_shader(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
void opengl_set_swap_interval(int interval);
void opengl_set_viewport(int x, int y, int width, int height);
void opengl_clear(Vec4 clear_color);

#ifdef _WIN32

#include <windows.h>
#include <GL/gl.h>

#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_INT_VEC2 0x8B53
#define GL_INT_VEC3 0x8B54
#define GL_INT_VEC4 0x8B55
#define GL_BOOL 0x8B56
#define GL_BOOL_VEC2 0x8B57
#define GL_BOOL_VEC3 0x8B58
#define GL_BOOL_VEC4 0x8B59
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C
#define GL_SAMPLER_1D 0x8B5D
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLER_3D 0x8B5F
#define GL_SAMPLER_CUBE 0x8B60
#define GL_SAMPLER_1D_SHADOW 0x8B61
#define GL_SAMPLER_2D_SHADOW 0x8B62
#define GL_DELETE_STATUS 0x8B80
#define GL_VALIDATE_STATUS 0x8B83
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FLOAT 0x1406
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_DEPTH_TEST 0x0B71
#define GL_CULL_FACE 0x0B44
#define GL_BLEND 0x0BE2
#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C
#define GL_NUM_EXTENSIONS 0x821D
#define GL_EXTENSIONS 0x1F03
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02
#define GL_FRONT_AND_BACK 0x0408
#define GL_LINE 0x1B01
#define GL_FILL 0x1B02
#define GL_TRIANGLES 0x0004
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_DST_ALPHA 0x0304
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_DST_COLOR 0x0306
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_BLEND_DST 0x0BE0
#define GL_BLEND_SRC 0x0BE1
#define GL_BLEND 0x0BE2
#define GL_ACTIVE_UNIFORMS 0x8B86

#if defined(_WIN32) && !defined(APIENTRY)
#define APIENTRY __stdcall
#endif

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef i8 GLbyte;
typedef u8 GLubyte;
typedef i16 GLshort;
typedef u16 GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef i32 GLclampx;
typedef int GLsizei;
typedef f32 GLfloat;
typedef f32 GLclampf;
typedef f64 GLdouble;
typedef f64 GLclampd;
typedef void* GLeglClientBufferEXT;
typedef void* GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;
typedef size_t GLsizeiptr;

#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_TYPE_RGBA_ARB 0x202B
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096

typedef struct WGLExtensions{
    int WGL_ARB_create_context_available;
    int WGL_ARB_create_context_profile_available;
    int WGL_EXT_swap_control_available;
    int WGL_ARB_pixel_format_available;
} WGLExtensions;

typedef const char* (APIENTRY* wglGetExtensionsStringARB_TYPE)(HDC);
typedef HGLRC (APIENTRY* wglCreateContextAttribsARB_TYPE)(HDC, HGLRC, const int*);
typedef BOOL (APIENTRY* wglChoosePixelFormatARB_TYPE)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);
typedef BOOL (APIENTRY* wglSwapIntervalEXT_TYPE)(int);

#elif __linux__

#include <GL/gl.h>
#include <GL/glx.h>

typedef struct GLXExtensions{
    int GLX_ARB_create_context_available;
    int GLX_ARB_create_context_profile_available;
    int MESA_swap_control_available;
} GLXExtensions;

typedef void (*glXSwapIntervalMESA_TYPE)(int);
typedef GLXContext (*glXCreateContextAttribsARB_TYPE)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

#endif

typedef GLuint (APIENTRY* glCreateShader_TYPE)(GLenum);
typedef void (APIENTRY* glShaderSource_TYPE)(GLuint, GLsizei, const GLchar**, const GLint*);
typedef void (APIENTRY* glCompileShader_TYPE)(GLuint);
typedef void (APIENTRY* glGetShaderiv_TYPE)(GLuint, GLenum, GLint*);
typedef void (APIENTRY* glDeleteShader_TYPE)(GLuint);
typedef void (APIENTRY* glGetShaderInfoLog_TYPE)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLuint (APIENTRY* glCreateProgram_TYPE)(void);
typedef void (APIENTRY* glAttachShader_TYPE)(GLuint, GLuint);
typedef void (APIENTRY* glLinkProgram_TYPE)(GLuint);
typedef void (APIENTRY* glGetProgramiv_TYPE)(GLuint, GLenum, GLint*);
typedef void (APIENTRY* glGetProgramInfoLog_TYPE)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (APIENTRY* glDeleteProgram_TYPE)(GLuint);
typedef void (APIENTRY* glGenBuffers_TYPE)(GLsizei, GLuint*);
typedef void (APIENTRY* glBindBuffer_TYPE)(GLenum, GLuint);
typedef void (APIENTRY* glBufferData_TYPE)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (APIENTRY* glVertexAttribPointer_TYPE)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (APIENTRY* glEnableVertexAttribArray_TYPE)(GLuint);
typedef void (APIENTRY* glUseProgram_TYPE)(GLuint);
typedef void (APIENTRY* glGenVertexArrays_TYPE)(GLsizei, GLuint*);
typedef void (APIENTRY* glBindVertexArray_TYPE)(GLuint);
typedef void (APIENTRY* glUniformMatrix4fv_TYPE)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (APIENTRY* glUniform3fv_TYPE)(GLint, GLsizei, GLfloat*);
typedef void (APIENTRY* glUniform1i_TYPE)(GLint, GLint);
typedef GLint (APIENTRY* glGetUniformLocation_TYPE)(GLuint, const GLchar*);
typedef const GLubyte* (APIENTRY* glGetStringi_TYPE)(GLenum, GLuint);
typedef void (APIENTRY* glGetActiveUniform_TYPE)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (APIENTRY* glDeleteProgram_TYPE)(GLuint);

extern glCreateShader_TYPE glCreateShader;
extern glShaderSource_TYPE glShaderSource;
extern glCompileShader_TYPE glCompileShader;
extern glGetShaderiv_TYPE glGetShaderiv;
extern glDeleteShader_TYPE glDeleteShader;
extern glGetShaderInfoLog_TYPE glGetShaderInfoLog;
extern glCreateProgram_TYPE glCreateProgram;
extern glAttachShader_TYPE glAttachShader;
extern glLinkProgram_TYPE glLinkProgram;
extern glGetProgramiv_TYPE glGetProgramiv;
extern glGetProgramInfoLog_TYPE glGetProgramInfoLog;
extern glDeleteProgram_TYPE glDeleteProgram;
extern glGenBuffers_TYPE glGenBuffers;
extern glBindBuffer_TYPE glBindBuffer;
extern glBufferData_TYPE glBufferData;
extern glVertexAttribPointer_TYPE glVertexAttribPointer;
extern glEnableVertexAttribArray_TYPE glEnableVertexAttribArray;
extern glUseProgram_TYPE glUseProgram;
extern glGenVertexArrays_TYPE glGenVertexArrays;
extern glBindVertexArray_TYPE glBindVertexArray;
extern glUniformMatrix4fv_TYPE glUniformMatrix4fv;
extern glUniform3fv_TYPE glUniform3fv;
extern glUniform1i_TYPE glUniform1i;
extern glGetUniformLocation_TYPE glGetUniformLocation;
extern glGetStringi_TYPE glGetStringi;
extern glGetActiveUniform_TYPE glGetActiveUniform;
extern glDeleteProgram_TYPE glDeleteProgram;