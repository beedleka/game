#pragma once

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct WindowSize{
    u32 width;
    u32 height;
} WindowSize;

typedef enum WindowState{
    WINDOWED,
    WINDOWED_FULLSCREEN,
    FULLSCREEN,
} WindowState;

typedef enum{
    RELEASED,
    PRESSED
} KeyState;

typedef struct MousePos{
    i32 x;
    i32 y;
} MousePos;

#define MAX_KEYCODES 255 // @Note maybe this should be different for each system?
extern KeyState keyboard[MAX_KEYCODES];

extern WindowState current_window_state;
extern WindowSize current_window_size;
extern u8 confine_cursor_to_center;

void window_close();
u8 window_create(const char* title, u32 width, u32 height);
u8 window_event();
void window_set_title(const char* title);
void window_set_resize_callback(void (*callback)());
void window_set_keyboard_callback(void (*callback)(u32, KeyState));
void window_set_mouse_callback(void (*callback)(MousePos));
void window_set_state(WindowState state);

#ifdef _WIN32

#include <windows.h>
#include <windowsx.h>

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((unsigned short) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((unsigned short) 0x02)
#endif

extern HDC device_context;

void win32_print_last_error(char* msg);

#define KEY_BACKSPACE VK_BACK
#define KEY_TAB VK_TAB
#define KEY_CLEAR VK_CLEAR
#define KEY_RETURN VK_RETURN
#define KEY_SHIFT VK_SHIFT
#define KEY_LEFTCTRL VK_LCONTROL
#define KEY_RIGHTCTRL VK_RCONTROL
#define KEY_LEFTSHIFT VK_LSHIFT
#define KEY_RIGHTSHIFT VK_RSHIFT
#define KEY_ALT VK_MENU
#define KEY_PAUSE VK_PAUSE
#define KEY_CAPSLOCK VK_CAPITAL
#define KEY_ESCAPE VK_ESCAPE
#define KEY_SPACE VK_SPACE
#define KEY_PAGEUP VK_PRIOR
#define KEY_PAGEDOWN VK_NEXT
#define KEY_HOME VK_HOME
#define KEY_LEFT VK_LEFT
#define KEY_RIGHT VK_RIGHT
#define KEY_UP VK_UP
#define KEY_DOWN VK_DOWN
#define KEY_SELECT VK_SELECT
#define KEY_PRINTSCREEN VK_SNAPSHOT
#define KEY_INSERT VK_INSERT
#define KEY_DELETE VK_DELETE
#define KEY_0 0x30
#define KEY_1 0x31
#define KEY_2 0x32
#define KEY_3 0x33
#define KEY_4 0x34
#define KEY_5 0x35
#define KEY_6 0x36
#define KEY_7 0x37
#define KEY_8 0x38
#define KEY_9 0x39
#define KEY_A 0x41
#define KEY_B 0x42
#define KEY_C 0x43
#define KEY_D 0x44
#define KEY_E 0x45
#define KEY_F 0x46
#define KEY_G 0x47
#define KEY_H 0x48
#define KEY_I 0x49
#define KEY_J 0x4A
#define KEY_K 0x4B
#define KEY_L 0x4C
#define KEY_M 0x4D
#define KEY_N 0x4E
#define KEY_O 0x4F
#define KEY_P 0x50
#define KEY_Q 0x51
#define KEY_R 0x52
#define KEY_S 0x53
#define KEY_T 0x54
#define KEY_U 0x55
#define KEY_V 0x56
#define KEY_W 0x57
#define KEY_X 0x58
#define KEY_Y 0x59
#define KEY_Z 0x5A
#define KEY_F1 VK_F1
#define KEY_F2 VK_F2
#define KEY_F3 VK_F3
#define KEY_F4 VK_F4
#define KEY_F5 VK_F5
#define KEY_F6 VK_F6
#define KEY_F7 VK_F7
#define KEY_F8 VK_F8
#define KEY_F9 VK_F9
#define KEY_F10 VK_F10
#define KEY_F11 VK_F11
#define KEY_F12 VK_F12

#elif __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>

extern Display* display;
extern Window window;

#endif