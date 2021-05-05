#pragma once

#include "types.h"
#include "utils.h"
#include "window.h"

#include <stdio.h>

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

#if defined(_WIN32) && !defined(APIENTRY)
#define APIENTRY __stdcall
#endif

#ifndef APIENTRY
#define APIENTRY
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

int opengl_init(int opengl_major_version, int opengl_minor_version);
void opengl_swap_buffers();
u32 opengl_load_shader(const char* vertex_shader_filename, const char* fragment_shader_filename);
void opengl_set_swap_interval(int interval);

typedef GLuint (APIENTRY* glCreateShader_TYPE)(GLenum);
glCreateShader_TYPE glCreateShader;
typedef void (APIENTRY* glShaderSource_TYPE)(GLuint, GLsizei, const GLchar**, const GLint*);
glShaderSource_TYPE glShaderSource;
typedef void (APIENTRY* glCompileShader_TYPE)(GLuint);
glCompileShader_TYPE glCompileShader;
typedef void (APIENTRY* glGetShaderiv_TYPE)(GLuint, GLenum, GLint*);
glGetShaderiv_TYPE glGetShaderiv;
typedef void (APIENTRY* glDeleteShader_TYPE)(GLuint);
glDeleteShader_TYPE glDeleteShader;
typedef void (APIENTRY* glGetShaderInfoLog_TYPE)(GLuint, GLsizei, GLsizei*, GLchar*);
glGetShaderInfoLog_TYPE glGetShaderInfoLog;
typedef GLuint (APIENTRY* glCreateProgram_TYPE)(void);
glCreateProgram_TYPE glCreateProgram;
typedef void (APIENTRY* glAttachShader_TYPE)(GLuint, GLuint);
glAttachShader_TYPE glAttachShader;
typedef void (APIENTRY* glLinkProgram_TYPE)(GLuint);
glLinkProgram_TYPE glLinkProgram;
typedef void (APIENTRY* glGetProgramiv_TYPE)(GLuint, GLenum, GLint*);
glGetProgramiv_TYPE glGetProgramiv;
typedef void (APIENTRY* glGetProgramInfoLog_TYPE)(GLuint, GLsizei, GLsizei*, GLchar*);
glGetProgramInfoLog_TYPE glGetProgramInfoLog;
typedef void (APIENTRY* glDeleteProgram_TYPE)(GLuint);
glDeleteProgram_TYPE glDeleteProgram;
typedef void (APIENTRY* glGenBuffers_TYPE)(GLsizei, GLuint*);
glGenBuffers_TYPE glGenBuffers;
typedef void (APIENTRY* glBindBuffer_TYPE)(GLenum, GLuint);
glBindBuffer_TYPE glBindBuffer;
typedef void (APIENTRY* glBufferData_TYPE)(GLenum, GLsizeiptr, const void*, GLenum);
glBufferData_TYPE glBufferData;
typedef void (APIENTRY* glVertexAttribPointer_TYPE)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
glVertexAttribPointer_TYPE glVertexAttribPointer;
typedef void (APIENTRY* glEnableVertexAttribArray_TYPE)(GLuint);
glEnableVertexAttribArray_TYPE glEnableVertexAttribArray;
typedef void (APIENTRY* glUseProgram_TYPE)(GLuint);
glUseProgram_TYPE glUseProgram;
typedef void (APIENTRY* glGenVertexArrays_TYPE)(GLsizei, GLuint*);
glGenVertexArrays_TYPE glGenVertexArrays;
typedef void (APIENTRY* glBindVertexArray_TYPE)(GLuint);
glBindVertexArray_TYPE glBindVertexArray;
typedef void (APIENTRY* glUniformMatrix4fv_TYPE)(GLint, GLsizei, GLboolean, const GLfloat*);
glUniformMatrix4fv_TYPE glUniformMatrix4fv;
typedef GLint (APIENTRY* glGetUniformLocation_TYPE)(GLuint, const GLchar*);
glGetUniformLocation_TYPE glGetUniformLocation;
typedef const GLubyte* (APIENTRY* glGetStringi_TYPE)(GLenum, GLuint);
glGetStringi_TYPE glGetStringi;

#ifdef _WIN32

#include <windows.h>
#include <GL/gl.h>

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
    int WGL_ARB_create_context;
    int WGL_ARB_create_context_profile;
    int WGL_EXT_swap_control;
    int WGL_ARB_pixel_format;
} WGLExtensions;

typedef struct GLExtensions{
    int GL_ARB_compute_shader;
} GLExtensions;

typedef const char* (APIENTRY* wglGetExtensionsStringARB_TYPE)(HDC);
wglGetExtensionsStringARB_TYPE wglGetExtensionsStringARB;
typedef HGLRC (APIENTRY* wglCreateContextAttribsARB_TYPE)(HDC, HGLRC, const int*);
wglCreateContextAttribsARB_TYPE wglCreateContextAttribsARB;
typedef BOOL (APIENTRY* wglChoosePixelFormatARB_TYPE)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);
wglChoosePixelFormatARB_TYPE wglChoosePixelFormatARB;
typedef BOOL (APIENTRY* wglSwapIntervalEXT_TYPE)(int);
wglSwapIntervalEXT_TYPE wglSwapIntervalEXT;

#endif