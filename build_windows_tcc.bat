@echo off
if [%1]==[] goto usage
if %1==debug tcc.exe *.c -lgdi32 -luser32 -lopengl32 -Wall -o game.exe
if %1==release tcc.exe *.c -lgdi32 -luser32 -lopengl32 -Wl,-subsystem=gui -o game.exe
goto end
:usage
echo usage: build_window_tcc.bat [debug ^| release]
:end