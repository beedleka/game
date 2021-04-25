#pragma once

#include "utils.h"

#ifdef _WIN32

#include "window.h"

#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>

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

PROC wglSwapInterval;
PROC glCreateShader;
PROC glShaderSource;
PROC glCompileShader;
PROC glGetShaderiv;
PROC glDeleteShader;
PROC glGetShaderInfoLog;
PROC glCreateProgram;
PROC glAttachShader;
PROC glLinkProgram;
PROC glGetProgramiv;
PROC glGetProgramInfoLog;
PROC glDeleteProgram;
PROC glGenBuffers;
PROC glBindBuffer;
PROC glBufferData;
PROC glVertexAttribPointer;
PROC glEnableVertexAttribArray;
PROC glUseProgram;
PROC glGenVertexArrays;
PROC glBindVertexArray;

int init_opengl_context();
int load_opengl_functions();
uint16 load_shader(const char* vertex_shader_filename, const char* fragment_shader_filename);

#endif