#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

#include <windows.h>

extern HDC device_context;

void close_window();
int create_window(char* title, int width, int height);
int event_loop();
void set_window_title(const char* title);

#endif