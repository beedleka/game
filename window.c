#include "window.h"

#ifdef _WIN32

HWND window_handle;
HDC device_context;
DWORD windowed_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
DWORD fullscreen_style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;
int quitting = 0;
window_state current_window_state = WINDOWED;
window_size current_window_size;
window_size original_window_size;

static void (*resize_callback)() = NULL;

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
                current_window_size.width = LOWORD(l_param);
                current_window_size.height = HIWORD(l_param);
                resize_callback();
            }
            break;
        case WM_KEYDOWN:
            switch(w_param){
                case VK_ESCAPE:
                    close_window();
                    break;
                case VK_F11:
                    if(current_window_state == WINDOWED){
                        set_fullscreen(WINDOWED_FULLSCREEN);
                    }
                    else{
                        set_fullscreen(WINDOWED);
                    }
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
    current_window_size.width = width;
    current_window_size.height = height;
    original_window_size.width = width;
    original_window_size.height = height;

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

    RECT window_rect = {0, 0, width, height};
    if(!AdjustWindowRect(&window_rect, windowed_style, FALSE)){
        win32_print_last_error("[ERROR] AdjustWindowRect:");
        return 1;
    }
    int adjusted_width = window_rect.right-window_rect.left;
    int adjusted_height = window_rect.bottom-window_rect.top;

    window_handle = CreateWindowEx(0,
        window_class_name, title, windowed_style,
        GetSystemMetrics(SM_CXSCREEN)/2-adjusted_width/2,
        GetSystemMetrics(SM_CYSCREEN)/2-adjusted_height/2,
        adjusted_width, adjusted_height,
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

void set_resize_callback(void (*callback)(int, int)){
    resize_callback = callback;
}

void set_fullscreen(window_state state){
    current_window_state = state;

    if(current_window_state == WINDOWED_FULLSCREEN){
        // DEVMODE graphics_mode = {0};
        // graphics_mode.dmSize = sizeof(DEVMODE);
        // graphics_mode.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
        // graphics_mode.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
        // graphics_mode.dmBitsPerPel = 32;
        // graphics_mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        // ChangeDisplaySettingsA(&graphics_mode, CDS_FULLSCREEN);
        SetWindowLongPtr(window_handle, GWL_STYLE, fullscreen_style);
        MoveWindow(window_handle, 0, 0, GetSystemMetrics(SM_CXSCREEN),
                                        GetSystemMetrics(SM_CYSCREEN), TRUE);
    }
    else if(current_window_state == WINDOWED){
        ChangeDisplaySettingsA(NULL, CDS_FULLSCREEN);
        RECT window_rect = {0, 0, original_window_size.width, original_window_size.height};
        SetWindowLongPtr(window_handle, GWL_STYLE, windowed_style);
        AdjustWindowRect(&window_rect, windowed_style, FALSE);
        int pos_x = GetSystemMetrics(SM_CXSCREEN)/2-original_window_size.width/2;
        int pos_y = GetSystemMetrics(SM_CYSCREEN)/2-original_window_size.height/2;
        MoveWindow(window_handle, pos_x, pos_y,
                    original_window_size.width,
                    original_window_size.height, TRUE);
    }
}

#endif