#pragma once

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct WindowSize{
    int width;
    int height;
} WindowSize;

typedef enum WindowState{
    WINDOWED,
    WINDOWED_FULLSCREEN,
    FULLSCREEN,
} WindowState;

extern WindowState current_window_state;
extern WindowSize current_window_size;

#ifdef _WIN32

#include <windows.h>

extern HDC device_context;

void window_close();
int window_create(char* title, int width, int height);
int window_event();
void window_set_title(const char* title);
void window_set_resize_callback(void (*callback)());
void window_set_state(WindowState state);

void win32_print_last_error(char* msg);

#endif