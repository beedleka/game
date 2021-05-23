@echo off
if [%1]==[] goto usage
if %1==debug clang.exe *.c -lopengl32 -lgdi32 -luser32 -Wno-deprecated-declarations -o game.exe
if %1==release clang.exe *.c -lgdi32 -luser32 -lopengl32 -Wno-deprecated-declarations -o game.exe -Wl,-SUBSYSTEM:WINDOWS,-ENTRY:mainCRTStartup
goto end
:usage
echo usage: build_window_clang.bat [debug ^| release]
:end