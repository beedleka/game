#include "opengl.h"

static int load_opengl_functions(){
    glCreateShader = (glCreateShader_TYPE)wglGetProcAddress("glCreateShader");
    if(glCreateShader == NULL) return 1;
    glCompileShader = (glCompileShader_TYPE)wglGetProcAddress("glCompileShader");
    if(glCompileShader == NULL) return 1;
    glShaderSource = (glShaderSource_TYPE)wglGetProcAddress("glShaderSource");
    if(glShaderSource == NULL) return 1;
    glGetShaderiv = (glGetShaderiv_TYPE)wglGetProcAddress("glGetShaderiv");
    if(glGetShaderiv == NULL) return 1;
    glDeleteShader = (glDeleteShader_TYPE)wglGetProcAddress("glDeleteShader");
    if(glDeleteShader == NULL) return 1;
    glGetShaderInfoLog = (glGetShaderInfoLog_TYPE)wglGetProcAddress("glGetShaderInfoLog");
    if(glGetShaderInfoLog == NULL) return 1;
    glCreateProgram = (glCreateProgram_TYPE)wglGetProcAddress("glCreateProgram");
    if(glCreateProgram == NULL) return 1;
    glAttachShader = (glAttachShader_TYPE)wglGetProcAddress("glAttachShader");
    if(glAttachShader == NULL) return 1;
    glLinkProgram = (glLinkProgram_TYPE)wglGetProcAddress("glLinkProgram");
    if(glLinkProgram == NULL) return 1;
    glGetProgramiv = (glGetProgramiv_TYPE)wglGetProcAddress("glGetProgramiv");
    if(glGetProgramiv == NULL) return 1;
    glGetProgramInfoLog = (glGetProgramInfoLog_TYPE)wglGetProcAddress("glGetProgramInfoLog");
    if(glGetProgramInfoLog == NULL) return 1;
    glDeleteProgram = (glDeleteProgram_TYPE)wglGetProcAddress("glDeleteProgram");
    if(glDeleteProgram == NULL) return 1;
    glGenBuffers = (glGenBuffers_TYPE)wglGetProcAddress("glGenBuffers");
    if(glGenBuffers == NULL) return 1;
    glBindBuffer = (glBindBuffer_TYPE)wglGetProcAddress("glBindBuffer");
    if(glBindBuffer == NULL) return 1;
    glBufferData = (glBufferData_TYPE)wglGetProcAddress("glBufferData");
    if(glBufferData == NULL) return 1;
    glVertexAttribPointer = (glVertexAttribPointer_TYPE)wglGetProcAddress("glVertexAttribPointer");
    if(glVertexAttribPointer == NULL) return 1;
    glEnableVertexAttribArray = (glEnableVertexAttribArray_TYPE)wglGetProcAddress("glEnableVertexAttribArray");
    if(glEnableVertexAttribArray == NULL) return 1;
    glUseProgram = (glUseProgram_TYPE)wglGetProcAddress("glUseProgram");
    if(glUseProgram == NULL) return 1;
    glGenVertexArrays = (glGenVertexArrays_TYPE)wglGetProcAddress("glGenVertexArrays");
    if(glGenVertexArrays == NULL) return 1;
    glBindVertexArray = (glBindVertexArray_TYPE)wglGetProcAddress("glBindVertexArray");
    if(glBindVertexArray == NULL) return 1;
    glUniformMatrix4fv = (glUniformMatrix4fv_TYPE)wglGetProcAddress("glUniformMatrix4fv");
    if(glUniformMatrix4fv == NULL) return 1;
    glGetUniformLocation = (glGetUniformLocation_TYPE)wglGetProcAddress("glGetUniformLocation");
    if(glGetUniformLocation == NULL) return 1;
    glGetStringi = (glGetStringi_TYPE)wglGetProcAddress("glGetStringi");
    if(glGetStringi == NULL) return 1;

    return 0;
}

#ifdef _WIN32

typedef struct wgl_extensions{
    int WGL_ARB_create_context;
    int WGL_ARB_create_context_profile;
    int WGL_EXT_swap_control;
    int WGL_ARB_pixel_format;
} wgl_extensions;

static wgl_extensions available_wgl_extensions = {0};

typedef struct gl_extensions{
    int GL_ARB_compute_shader;
} gl_extensions;

static gl_extensions available_gl_extensions = {0};

static int load_wgl_functions(){
    if(available_wgl_extensions.WGL_EXT_swap_control){
        wglSwapIntervalEXT = (wglSwapIntervalEXT_TYPE)wglGetProcAddress("wglSwapIntervalEXT");
        if(wglSwapIntervalEXT == NULL) return 1;
    }

    return 0;
}

/*
    1/ Create a dummy window class/window
    2/ Find and set a kinda good pixel format (descriptor -> ChoosePixelFormat -> DescribePixelFormat)
    3/ Create a legacy OpenGL context (wglCreateContext)
    4/ Find wglGetExtensionsStringARB function pointer and use it to retrieve wgl extensions
    5/ Parse wgl extensions list and fill available_wgl_extensions
    6/ If WGL_ARB_create_context, WGL_ARB_create_context_profile, WGL_ARB_pixel_format are available
       proceed to retrieve wglChoosePixelFormatARB and wglCreateContextAttribsARB
    7/ Find pixel format with pixel_format_attributes -> wglChoosePixelFormatARB -> DescribePixelFormat
    8/ Create a new OpenGL context and set it as current (wglCreateContextAttribsARB)
    9/ Load wgl extension functions
    10/ Load OpenGL functions
    11/ Check OpenGL extensions
*/
int init_opengl_context(int opengl_major_version, int opengl_minor_version){
    if(device_context == NULL){
        error("init_opengl_context: A window is needed for opengl context creation");
        return 1;
    }

    WNDCLASS dummy_class = {0};
    dummy_class.style = CS_OWNDC;
    dummy_class.lpfnWndProc = DefWindowProc;
    dummy_class.hInstance = GetModuleHandle(0);
    dummy_class.lpszClassName = "dummy_window_class";

    if(!RegisterClass(&dummy_class)){
        win32_print_last_error("[ERROR] RegisterClass:");
        return 1;
    }

    HWND dummy_window_handle = CreateWindowEx(0,
        "dummy_window_class",
        "",
        WS_OVERLAPPEDWINDOW,
        0, 0,
        0, 0, NULL, NULL, dummy_class.hInstance, NULL);

    if(!dummy_window_handle){
        win32_print_last_error("[ERROR] CreateWindow:");
        return 1;
    }

    HDC dummy_device_context = GetDC(dummy_window_handle);

    PIXELFORMATDESCRIPTOR dummy_pixel_format = {0};
    dummy_pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    dummy_pixel_format.nVersion = 1;
    dummy_pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    dummy_pixel_format.iPixelType = PFD_TYPE_RGBA;
    dummy_pixel_format.cColorBits = 32;
    dummy_pixel_format.cDepthBits = 24;
    dummy_pixel_format.cStencilBits = 8;
    int dummy_pixel_format_id = ChoosePixelFormat(dummy_device_context, &dummy_pixel_format);

    if(dummy_pixel_format_id == 0){
        error("ChoosePixelFormat: no suitable pixel format found");
        return 1;
    }

    PIXELFORMATDESCRIPTOR good_dummy_pixel_format;
    if(!DescribePixelFormat(dummy_device_context,
                            dummy_pixel_format_id,
                            sizeof(PIXELFORMATDESCRIPTOR),
                            &good_dummy_pixel_format)){
        win32_print_last_error("[ERROR] DescribePixelFormat:");
        return 1;
    }

    if(!SetPixelFormat(dummy_device_context, dummy_pixel_format_id, &good_dummy_pixel_format)){
        win32_print_last_error("[ERROR] SetPixelFormat:");
        return 1;
    }

    HGLRC dummy_opengl_context = wglCreateContext(dummy_device_context);
    if(dummy_opengl_context == NULL){
        win32_print_last_error("[ERROR] wglCreateContext:");
        return 1;
    }

    if(!wglMakeCurrent(dummy_device_context, dummy_opengl_context)){
        win32_print_last_error("[ERROR] wglMakeCurrent:");
        return 1;
    }

    int err = 0;

    /* @Note Should we use wglGetExtensionsStringARB or wglGetExtensionsStringEXT ? */
    wglGetExtensionsStringARB = (wglGetExtensionsStringARB_TYPE)wglGetProcAddress("wglGetExtensionsStringARB");
    if(wglGetExtensionsStringARB == NULL){
        error("wglGetExtensionsStringARB is NULL");
        err = 1;
    }

    const char* wgl_extensions_string = wglGetExtensionsStringARB(dummy_device_context);

    const char* begin = wgl_extensions_string;
    const char* end = begin;
    ptr size;

    while(*begin != '\0'){
        while(*begin == ' ') begin++;
        end = begin;
        while(*end != '\0' && *end != ' ') end++;
        size = end-begin;

        if(size > 0){
            if(str_equals(begin, size, "WGL_ARB_create_context")) available_wgl_extensions.WGL_ARB_create_context = 1;
            if(str_equals(begin, size, "WGL_ARB_create_context_profile")) available_wgl_extensions.WGL_ARB_create_context_profile = 1;
            if(str_equals(begin, size, "WGL_EXT_swap_control")) available_wgl_extensions.WGL_EXT_swap_control  = 1;
            if(str_equals(begin, size, "WGL_ARB_pixel_format")) available_wgl_extensions.WGL_ARB_pixel_format  = 1;
            // @Remove
            // for(ptr i = 0; i < size; i++){
            //     printf("%c", *(begin+i));
            // }
            // printf("\n");
        }
        begin = end;
    }

    if(!available_wgl_extensions.WGL_ARB_create_context){
        error("WGL_ARB_create_context not available");
        err = 1;
    }
    if(!available_wgl_extensions.WGL_ARB_create_context_profile){
        error("WGL_ARB_create_context_profile not available");
        err = 1;
    }
    if(!available_wgl_extensions.WGL_ARB_pixel_format){
        error("WGL_ARB_pixel_format not available");
        err = 1;
    }

    if(!err){
        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_TYPE)wglGetProcAddress("wglCreateContextAttribsARB");
        if(wglCreateContextAttribsARB == NULL){
            error("eglCreateContextAttribsARB is NULL");
            err = 1;
        }

        wglChoosePixelFormatARB = (wglChoosePixelFormatARB_TYPE)wglGetProcAddress("wglChoosePixelFormatARB");
        if(wglChoosePixelFormatARB == NULL){
            error("wglChoosePixelFormatARB is NULL");
            err = 1;
        }
    }

    if(!wglDeleteContext(dummy_opengl_context)){
        win32_print_last_error("[ERROR] wglDeleteContext:");
        err = 1;
    }
    if(!ReleaseDC(dummy_window_handle, dummy_device_context)){
        win32_print_last_error("[ERROR] ReleaseDC:");
        err = 1;
    }
    if(!DestroyWindow(dummy_window_handle)){
        win32_print_last_error("[ERROR] DestroyWindow:");
        err = 1;
    }
    if(!UnregisterClass("dummy_window_class", dummy_class.hInstance)){
        win32_print_last_error("[ERROR] UnregisterClass:");
        err = 1;
    }

    if(err) return err;

    const int pixel_format_attributes[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0,
    };

    int pixel_format;
    UINT num_formats;
    wglChoosePixelFormatARB(device_context, pixel_format_attributes,
                            NULL, 1, &pixel_format, &num_formats);

    PIXELFORMATDESCRIPTOR good_pixel_format;
    if(!DescribePixelFormat(device_context,
                            pixel_format,
                            sizeof(PIXELFORMATDESCRIPTOR),
                            &good_pixel_format)){
        win32_print_last_error("[ERROR] DescribePixelFormat:");
        return 1;
    }

    if(!SetPixelFormat(device_context, pixel_format, &good_pixel_format)){
        win32_print_last_error("[ERROR] SetPixelFormat:");
        return 1;
    }

    const int context_attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, opengl_major_version,
        WGL_CONTEXT_MINOR_VERSION_ARB, opengl_minor_version,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    HGLRC opengl_context = wglCreateContextAttribsARB(device_context, 0, context_attributes);

    if(opengl_context == NULL){
        char* error_message;
        /* @Note On some hardware ERROR_INVALID_VERSION_ARB is 0xC0072095 instead of 0x2095 */
        switch(GetLastError() & 0x0000FFFF){
            case ERROR_INVALID_VERSION_ARB:
                error_message = "Invalid or unsupported OpenGL version.";
                break;
            case ERROR_INVALID_PROFILE_ARB:
                error_message = "Invalid or unsupported OpenGL profile.";
                break;
            default:
                error_message = "Unknown error.";
                break;
        }

        error("wglMakeCurrent: %s", error_message);
        return 1;
    }

    if(!wglMakeCurrent(device_context, opengl_context)){
        win32_print_last_error("[ERROR] wglMakeCurrent:");
        return 1;
    }

    err = load_wgl_functions();
    if(err){
        win32_print_last_error("[ERROR] load_wgl_functions:");
        return 1;
    }

    err = load_opengl_functions();
    if(err){
        win32_print_last_error("[ERROR] load_opengl_functions:");
        return 1;
    }

    int major;
    int minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    if(major != opengl_major_version || minor != opengl_minor_version){
        error("Got wrong OpengGL version");
        return 1;
    }

    info("Loaded OpenGL context %d.%d", major, minor);

    int extensions_count;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensions_count);
    for(int i = 0; i < extensions_count; i++){
        const unsigned char* extension = glGetStringi(GL_EXTENSIONS, i);
        if(strcmp((char*)extension, "GL_ARB_compute_shader")) available_gl_extensions.GL_ARB_compute_shader = 1;
    }

    return 0;
}

void swap_buffers(){
    SwapBuffers(device_context);
}

void set_swap_interval(int interval){
    if(wglSwapIntervalEXT == NULL){
        error("set_swap_interval: wglSwapIntervalEXT isn't available");
        return;
    }
    wglSwapIntervalEXT(interval);
}

#endif

u16 load_shader(const char* vertex_shader_filename, const char* fragment_shader_filename){
    FILE* vertex_shader_file = fopen(vertex_shader_filename, "rb");
    FILE* fragment_shader_file = fopen(fragment_shader_filename, "rb");

    if(vertex_shader_file == NULL){
        error("load_shader: no such file or directory \"%s\"", vertex_shader_filename);
        return 0;
    }

    if(fragment_shader_file == NULL){
        error("load_shader: no such file or directory \"%s\"", fragment_shader_filename);
        return 0;
    }

    int success;
    char info[512];

    char* vertex_shader_text;
    const char* tmp;
    load_file_to_buffer(vertex_shader_file, &vertex_shader_text);
    fclose(vertex_shader_file);
    u16 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    tmp = vertex_shader_text;
    glShaderSource(vertex_shader, 1, &tmp, NULL);
    free(vertex_shader_text);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info);
        error("load_shader: Failed to compile vertex shader:\n%s", info);
        glDeleteShader(vertex_shader);
        return 0;
    }

    char* fragment_shader_text;
    load_file_to_buffer(fragment_shader_file, &fragment_shader_text);
    fclose(fragment_shader_file);
    u16 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    tmp = fragment_shader_text;
    glShaderSource(fragment_shader, 1, &tmp, NULL);
    free(fragment_shader_text);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, info);
        error("load_shader: Failed to compile fragment shader:\n%s", info);
        glDeleteShader(fragment_shader);
        return 0;
    }

    u16 shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader_program, 512, NULL, info);
        glDeleteProgram(shader_program);
        error("load_shader: Failed to link shader program:\n%s", info);
        return 0;
    }

    return shader_program;
}