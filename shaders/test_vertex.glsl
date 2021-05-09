#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in float a_color;

uniform mat4 mvp;

flat out int color;

void main(){
    gl_Position = mvp*vec4(a_position, 1.0);
    color = int(a_color);
}