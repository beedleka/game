#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;

uniform mat4 mvp;

out vec2 texcoord;

void main(){
    gl_Position = mvp*vec4(a_position, 1.0);
    texcoord = a_texcoord;
}