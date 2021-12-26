#!/bin/bash
i686-w64-mingw32-gcc *.c -lopengl32 -luser32 -lgdi32 -Wall -Wextra -Wno-ignored-qualifiers -Wno-cast-function-type -Wno-missing-braces -o game.exe