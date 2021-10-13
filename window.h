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

typedef struct MouseMove{
    i32 dx;
    i32 dy;
} MouseMove;

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
void window_set_mouse_callback(void (*callback)(MouseMove));
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
#include  <X11/Xatom.h>
#include <X11/extensions/XInput2.h>

#define KEY_BACKSPACE 22
#define KEY_TAB 23
// #define KEY_CLEAR @Note
#define KEY_RETURN 36
#define KEY_LEFTCTRL 37
#define KEY_RIGHTCTRL 105
#define KEY_LEFTSHIFT 50
#define KEY_RIGHTSHIFT 62
#define KEY_ALT 64
// #define KEY_PAUSE
#define KEY_CAPSLOCK 66
#define KEY_ESCAPE 9
#define KEY_SPACE 65
#define KEY_PAGEUP 112
#define KEY_PAGEDOWN 117
#define KEY_HOME 110
#define KEY_LEFT 113
#define KEY_RIGHT 114
#define KEY_UP 111
#define KEY_DOWN 116
// #define KEY_SELECT
// #define KEY_PRINTSCREEN 
#define KEY_INSERT 118
#define KEY_DELETE 119
#define KEY_0 19
#define KEY_1 10
#define KEY_2 11
#define KEY_3 12
#define KEY_4 13
#define KEY_5 14
#define KEY_6 15
#define KEY_7 16
#define KEY_8 17
#define KEY_9 18
#define KEY_A 38
#define KEY_B 56
#define KEY_C 54
#define KEY_D 40
#define KEY_E 26
#define KEY_F 41
#define KEY_G 42
#define KEY_H 43
#define KEY_I 31
#define KEY_J 44
#define KEY_K 45
#define KEY_L 46
#define KEY_M 58
#define KEY_N 57
#define KEY_O 32
#define KEY_P 33
#define KEY_Q 24
#define KEY_R 27
#define KEY_S 39
#define KEY_T 28
#define KEY_U 30
#define KEY_V 55
#define KEY_W 25
#define KEY_X 53
#define KEY_Y 29
#define KEY_Z 52
#define KEY_F1 67
#define KEY_F2 68
#define KEY_F3 69
#define KEY_F4 70
#define KEY_F5 71
#define KEY_F6 72
#define KEY_F7 73
#define KEY_F8 74
#define KEY_F9 75
#define KEY_F10 76
#define KEY_F11 95
#define KEY_F12 96

extern Display* display;
extern Window window;

#endif