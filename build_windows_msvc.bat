@echo off
if not defined DevEnvDir (
    call vcvarsall.bat x64
)
if [%1]==[] goto usage
if %1==debug cl *.c user32.lib gdi32.lib Opengl32.lib /DEBUG /Fegame.exe
if %1==release cl *.c user32.lib gdi32.lib Opengl32.lib /Fegame.exe /link /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup
del *.obj
goto end
:usage
echo usage: build_window_msvc.bat [debug ^| release]
:end