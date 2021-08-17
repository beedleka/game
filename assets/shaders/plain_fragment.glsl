#version 330 core

out vec4 frag_color;

in vec2 texcoord;

uniform vec3 color;
uniform sampler2D tex;

void main(){
    frag_color = texture(tex, texcoord);
}
