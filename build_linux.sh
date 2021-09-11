#!/bin/bash
gcc *.c -lm -lX11 -lGL -lXi -D X11 -Wall -Wextra -Wno-ignored-qualifiers -Wno-cast-function-type -Wno-missing-braces -o game.out