@echo off
if [%1]==[] goto usage
if %1==debug gcc.exe *.c -lopengl32 -lgdi32 -Wall -Wextra -Wno-ignored-qualifiers -Wno-cast-function-type -Wno-missing-braces -o game.exe
if %1==release gcc.exe *.c -lopengl32 -lgdi32 -mwindows -o game.exe
goto end
:usage
echo usage: build_window_gcc.bat [debug ^| release]
:end