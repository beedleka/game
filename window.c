#include "window.h"

WindowState current_window_state = WINDOWED;
WindowSize current_window_size;
WindowSize original_window_size;
u8 confine_cursor_to_center = 1;

KeyState keyboard[MAX_KEYCODES] = {RELEASED};

void empty_callback(){};
static void (*resize_callback)() = (void(*)())empty_callback;
static void (*keyboard_callback)(u32, KeyState) = (void(*)(u32, KeyState))empty_callback;
static void (*mouse_callback)(MouseMove) = (void(*)(MouseMove))empty_callback;

void window_set_resize_callback(void (*callback)()){
    resize_callback = callback;
}

void window_set_keyboard_callback(void (*callback)(u32, KeyState)){
    keyboard_callback = callback;
}

void window_set_mouse_callback(void (*callback)(MouseMove)){
    mouse_callback = callback;
}

#ifdef _WIN32

HWND window_handle;
HDC device_context;
DWORD windowed_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
DWORD fullscreen_style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;

void window_close(){
    if(!ReleaseDC(window_handle, device_context)){
        win32_print_last_error("ReleaseDC:");
    }

    if(!DestroyWindow(window_handle)){
        win32_print_last_error("DestroyWindow:");
    }

    if(!UnregisterClass("window_class", GetModuleHandle(0))){
        win32_print_last_error("UnregisterClass:");
    }
    window_handle = NULL;
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
            keyboard_callback(w_param, PRESSED);
            keyboard[w_param] = PRESSED;
            break;
        case WM_KEYUP:
            keyboard_callback(w_param, RELEASED);
            keyboard[w_param] = RELEASED;
            break;
        case WM_INPUT:
            {
                UINT size = sizeof(RAWINPUT);
                RAWINPUT raw_input[sizeof(RAWINPUT)];
                GetRawInputData((HRAWINPUT)l_param, RID_INPUT, raw_input, &size, sizeof(RAWINPUTHEADER));
                if(raw_input->header.dwType == RIM_TYPEMOUSE){
                    mouse_callback((MouseMove){raw_input->data.mouse.lLastX, raw_input->data.mouse.lLastY});
                }

                if(confine_cursor_to_center){
                    RECT rect;
                    GetWindowRect(window_handle, &rect);
                    SetCursorPos((rect.right+rect.left)/2, (rect.top+rect.bottom)/2);
                }
            }
            break;
        case WM_CLOSE:
            window_close();
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

u8 window_create(const char* title, u32 width, u32 height){
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
        win32_print_last_error("RegisterClass:");
        return 1;
    }

    RECT window_rect = {0, 0, width, height};
    if(!AdjustWindowRect(&window_rect, windowed_style, 0)){
        win32_print_last_error("AdjustWindowRect:");
        return 1;
    }
    u32 adjusted_width = window_rect.right-window_rect.left;
    u32 adjusted_height = window_rect.bottom-window_rect.top;

    window_handle = CreateWindowEx(0,
        window_class_name, title, windowed_style,
        GetSystemMetrics(SM_CXSCREEN)/2-adjusted_width/2,
        GetSystemMetrics(SM_CYSCREEN)/2-adjusted_height/2,
        adjusted_width, adjusted_height,
        NULL, NULL, window_class.hInstance, NULL);

    if(!window_handle){
        win32_print_last_error("CreateWindowEx:");
        return 1;
    }

    device_context = GetDC(window_handle);
    if(device_context == NULL){
        win32_print_last_error("CreateWindowEx:");
        return 1;
    }

    ShowWindow(window_handle, 5);

    ShowCursor(0);

    RAWINPUTDEVICE raw_input_device[1];
    raw_input_device[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    raw_input_device[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    raw_input_device[0].dwFlags = RIDEV_INPUTSINK;
    raw_input_device[0].hwndTarget = window_handle;
    if(!RegisterRawInputDevices(raw_input_device, 1, sizeof(raw_input_device[0]))){
        win32_print_last_error("RegisterRawInputDevices:");
        return 1;
    }

    return 0;
}

u8 window_event(){
    MSG message;
    while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
        if(message.message != WM_QUIT){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else{
            return 0;
        }
    }
    return 1;
}

void window_set_title(const char* title){
    if(window_handle == NULL) return;
    if(!SetWindowTextA(window_handle, title)){
        win32_print_last_error("SetWindowTextA:");
    }
}

void window_set_state(WindowState state){
    current_window_state = state;

    if(current_window_state == WINDOWED_FULLSCREEN){
        // @Note Investigate difference between "exclusive fullscreen" and "borderless fullscreen"
        // DEVMODE graphics_mode = {0};
        // graphics_mode.dmSize = sizeof(DEVMODE);
        // graphics_mode.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
        // graphics_mode.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
        // graphics_mode.dmBitsPerPel = 32;
        // graphics_mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        // ChangeDisplaySettingsA(&graphics_mode, CDS_FULLSCREEN);
        SetWindowLongPtr(window_handle, GWL_STYLE, fullscreen_style);
        MoveWindow(window_handle, 0, 0, GetSystemMetrics(SM_CXSCREEN),
                                        GetSystemMetrics(SM_CYSCREEN), 1);
    }
    else if(current_window_state == WINDOWED){
        ChangeDisplaySettingsA(NULL, CDS_FULLSCREEN);
        RECT window_rect = {0, 0, original_window_size.width, original_window_size.height};
        SetWindowLongPtr(window_handle, GWL_STYLE, windowed_style);
        AdjustWindowRect(&window_rect, windowed_style, 0);
        u32 pos_x = GetSystemMetrics(SM_CXSCREEN)/2-original_window_size.width/2;
        u32 pos_y = GetSystemMetrics(SM_CYSCREEN)/2-original_window_size.height/2;
        MoveWindow(window_handle, pos_x, pos_y,
                    original_window_size.width,
                    original_window_size.height, 1);
    }
}

#elif __linux__

#ifdef X11

Display* display;
Window window;
Atom delete_window_atom;
Atom proprety_atom;

u8 window_create(const char* title, u32 width, u32 height){
    current_window_size.width = width;
    current_window_size.height = height;
    original_window_size.width = width;
    original_window_size.height = height;

    display = XOpenDisplay(0);
    if(display == NULL){
        error("XOpenDisplay: Failed to open display");
        return 1;
    }

    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, width, height,
                                0, 0, 0);
    XSetStandardProperties(display, window, title, title, None, NULL, 0, NULL);

    XSelectInput(display, window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask
                    | PointerMotionMask);

    delete_window_atom = XInternAtom(display, "WM_DELETE_WINDOW", 1);
    proprety_atom = XInternAtom(display, "_MOTIF_WM_HINTS", 1);
    XSetWMProtocols(display, window, &delete_window_atom, 1);
    XMapWindow(display, window);


    i32 xi_opcode, event_return, error_return;
    if(!XQueryExtension(display, "XInputExtension", &xi_opcode, &event_return, &error_return)){
        warn("XInputExtension not supported");
    }
    i32 major = 2;
    i32 minor = 0;
    XIQueryVersion(display, &major, &minor);
    if(major != 2 || minor != 0){
        warn("XIQueryVersion didn't return 2.0");
    }

    // @Note we shouldn't do this if XInput isn't available, add a mouse fallback using MotionNotify
    XIEventMask event_mask;
    u8 mask[XIMaskLen(XI_RawMotion)] = { 0 };
    event_mask.deviceid = XIAllMasterDevices;
    event_mask.mask_len = sizeof(mask);
    event_mask.mask = mask;
    XISetMask(mask, XI_RawMotion);
    i32 screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);
    XISelectEvents(display, root, &event_mask, 1);

    return 0;
}

u8 window_closed = 0;

u8 window_event(){
    if(window_closed){
        return 0;
    }

    XPending(display);
    while(QLength(display)){
        XEvent event;
        XNextEvent(display, &event);
        if(event.type == ClientMessage){
            if(event.xclient.data.l[0] == (long int)delete_window_atom){
                return 0;
            }
        }
        else if(event.type == DestroyNotify){ // @Note why doesn't this work? have to use window_closed
            return 0;
        }
        else if(event.type == KeyPress){
            keyboard_callback(event.xkey.keycode, PRESSED);
            keyboard[event.xkey.keycode] = PRESSED;
        }
        else if(event.type == KeyRelease){
            keyboard_callback(event.xkey.keycode, RELEASED);
            keyboard[event.xkey.keycode] = RELEASED;
        }
        else if(event.type == GenericEvent){
            if(XGetEventData(display, &event.xcookie)){
                XIRawEvent* raw_event = event.xcookie.data;
                f64* raw_values = raw_event->raw_values;
                mouse_callback((MouseMove){(i32)raw_values[0], (i32)raw_values[1]});
            }
        }
        else if(event.type == ConfigureNotify){
            current_window_size.width = event.xconfigure.width;
            current_window_size.height = event.xconfigure.height;
            resize_callback();
        }
    }

    return 1;
}

void window_set_title(const char* title){
    XSetStandardProperties(display, window, title, title, None, NULL, 0, NULL);
}

typedef struct {
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long inputMode;
    unsigned long status;
} Hints;

void window_set_state(WindowState state){
    current_window_state = state;
    Hints hints;
    hints.flags = 2;
    hints.decorations = current_window_state == WINDOWED;
    XChangeProperty(display, window, proprety_atom, proprety_atom,32,
        PropModeReplace, (unsigned char*)&hints, 5);

    XMoveResizeWindow(display, window, 0, 0, current_window_size.width, current_window_size.height);
    XMapRaised(display, window);
    XGrabPointer(display, window, 1, 0, GrabModeAsync, GrabModeAsync, window, 0L, CurrentTime);
    XGrabKeyboard(display, window, 0, GrabModeAsync, GrabModeAsync, CurrentTime);
}

void window_close(){
    XDestroyWindow(display, window);
    window_closed = 1;
}

#endif

#endif