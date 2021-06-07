#include "mesh.h"

// Wavefront obj loader
int load_mesh(char* mesh_filepath){
    FILE* mesh_file = fopen(mesh_filepath, "rb");
    if(mesh_file == NULL){
        error("load_mesh: no such file or directory \"%s\"", mesh_filepath);
        return 1;
    }

    char* c;
    load_file_to_buffer(mesh_file, &c);
    fclose(mesh_file);

    while(*c != '\0'){
        if(*c == '\n'){
            printf(" \\n\n");
        }
        if(*c == 'v' && *(c+1) == ' '){
            c++;
            // printf("%c\n", *(c+1));
        }
        c++;
    }

    free(c);
    return 0;
}