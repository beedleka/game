#!/bin/bash
gcc *.c -lm -lX11 -lGL -D X11 -Wall -Wextra -Wno-ignored-qualifiers -Wno-cast-function-type -Wno-missing-braces -o game