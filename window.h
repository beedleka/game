#pragma once

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct window_size{
    int width;
    int height;
} window_size;

typedef enum window_state{
    WINDOWED,
    WINDOWED_FULLSCREEN,
    FULLSCREEN,
} window_state;

extern window_state current_window_state;
extern window_size current_window_size;

#ifdef _WIN32

#include <windows.h>

extern HDC device_context;

void close_window();
int create_window(char* title, int width, int height);
int event_loop();
void set_window_title(const char* title);
void set_resize_callback(void (*callback)(int, int));
void set_fullscreen(window_state state);

void win32_print_last_error(char* msg);

#endif