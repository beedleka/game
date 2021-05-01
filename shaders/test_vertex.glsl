#version 330 core

layout (location = 0) in vec3 a_position;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main(){
    mat4 mvp = p*v*m;
    gl_Position = mvp*vec4(a_position, 1.0);
}