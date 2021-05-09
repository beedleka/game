#version 330 core

out vec4 frag_color;

flat in int color;

void main(){
    if(color == 0){
        frag_color = vec4(1, 0, 0, 1);
    }
    else if(color == 1){
        frag_color = vec4(0, 1, 0, 1);
    }
    else if(color == 2){
        frag_color = vec4(0, 0, 1, 1);
    }
    else if(color == 3){
        frag_color = vec4(1, 0, 1, 1);
    }
    else if(color == 4){
        frag_color = vec4(0, 1, 1, 1);
    }
    else if(color == 5){
        frag_color = vec4(1, 1, 0, 1);
    }
}
