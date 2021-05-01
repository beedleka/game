#include "window.h"

#ifdef _WIN32

HWND window_handle;
HDC device_context;
DWORD window_style;
int quitting = 0;

static void (*resize_callback)(int, int) = NULL;

void close_window(){
    quitting = 1;
    if(!ReleaseDC(window_handle, device_context)){
        win32_print_last_error("[ERROR] ReleaseDC:");
    }

    if(!DestroyWindow(window_handle)){
        win32_print_last_error("[ERROR] DestroyWindow:");
    }

    if(!UnregisterClass("window_class", GetModuleHandle(0))){
        win32_print_last_error("[ERROR] UnregisterClass:");
    }
}

static LRESULT CALLBACK window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param){
    switch(message){
        case WM_SIZE:
            if(resize_callback != NULL){
                resize_callback(LOWORD(l_param), HIWORD(l_param));
            }
            break;
        case WM_KEYDOWN:
            switch(w_param){
                case VK_ESCAPE:
                    close_window();
                    break;
            }
            break;
        case WM_CLOSE:
            close_window();
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(window_handle, message, w_param, l_param);
    }
    return 0;
}

void win32_print_last_error(char* msg){
    wchar_t buff[256];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS |
        FORMAT_MESSAGE_MAX_WIDTH_MASK,
        NULL, GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        buff, (sizeof(buff)/sizeof(wchar_t)), NULL);
    error("%s %S", msg, buff);
}

int create_window(char* title, int width, int height){
    const char* window_class_name = "window_class";
    WNDCLASS window_class = {0};
    window_class.style = CS_OWNDC;
    window_class.lpfnWndProc = window_procedure;
    window_class.hInstance = GetModuleHandle(0);
    window_class.lpszClassName = window_class_name;

    if(!RegisterClass(&window_class)){
        win32_print_last_error("[ERROR] RegisterClass:");
        return 1;
    }

    window_style = WS_OVERLAPPEDWINDOW;

    RECT window_rect = {0, 0, width, height};
    if(!AdjustWindowRect(&window_rect, window_style, FALSE)){
        win32_print_last_error("[ERROR] AdjustWindowRect:");
        return 1;
    }

    window_handle = CreateWindowEx(0,
        window_class_name,
        title,
        window_style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        window_rect.right-window_rect.left,
        window_rect.bottom-window_rect.top,
        NULL, NULL, window_class.hInstance, NULL);

    if(!window_handle){
        win32_print_last_error("[ERROR] CreateWindowEx:");
        return 1;
    }

    device_context = GetDC(window_handle);
    if(device_context == NULL){
        win32_print_last_error("[ERROR] CreateWindowEx:");
        return 1;
    }

    ShowWindow(window_handle, 5);

    return 0;
}

int event_loop(){
    MSG message;
    PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
    if(message.message != WM_QUIT){
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.message != WM_QUIT;
}

void set_window_title(const char* title){
    if(quitting) return;
    if(!SetWindowTextA(window_handle, title)){
        win32_print_last_error("[ERROR] SetWindowTextA:");
    }
}

window_size get_window_size(){
    RECT window_rect;
    GetClientRect(window_handle, &window_rect);
    return (window_size){window_rect.right, window_rect.bottom};
}

void set_resize_callback(void (*callback)(int, int)){
    resize_callback = callback;
}

#endif