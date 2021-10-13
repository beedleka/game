#include "opengl.h"

glCreateShader_TYPE glCreateShader;
glShaderSource_TYPE glShaderSource;
glCompileShader_TYPE glCompileShader;
glGetShaderiv_TYPE glGetShaderiv;
glDeleteShader_TYPE glDeleteShader;
glGetShaderInfoLog_TYPE glGetShaderInfoLog;
glCreateProgram_TYPE glCreateProgram;
glAttachShader_TYPE glAttachShader;
glLinkProgram_TYPE glLinkProgram;
glGetProgramiv_TYPE glGetProgramiv;
glGetProgramInfoLog_TYPE glGetProgramInfoLog;
glDeleteProgram_TYPE glDeleteProgram;
glGenBuffers_TYPE glGenBuffers;
glBindBuffer_TYPE glBindBuffer;
glBufferData_TYPE glBufferData;
glVertexAttribPointer_TYPE glVertexAttribPointer;
glEnableVertexAttribArray_TYPE glEnableVertexAttribArray;
glUseProgram_TYPE glUseProgram;
glGenVertexArrays_TYPE glGenVertexArrays;
glBindVertexArray_TYPE glBindVertexArray;
glUniformMatrix4fv_TYPE glUniformMatrix4fv;
glUniform3fv_TYPE glUniform3fv;
glUniform1i_TYPE glUniform1i;
glGetUniformLocation_TYPE glGetUniformLocation;
glGetStringi_TYPE glGetStringi;
glGetActiveUniform_TYPE glGetActiveUniform;
glGenerateMipmap_TYPE glGenerateMipmap;
glGetBufferSubData_TYPE glGetBufferSubData;
glDeleteVertexArrays_TYPE glDeleteVertexArrays;
glDeleteBuffers_TYPE glDeleteBuffers;

void* get_proc_address(const char* name){
#ifdef _WIN32
    return wglGetProcAddress(name);
#elif __linux__
#ifdef X11
    return glXGetProcAddress((const GLubyte *)name);
#endif
#endif
}

static u8 load_opengl_functions(){
    glCreateShader = (glCreateShader_TYPE)get_proc_address("glCreateShader");
    if(glCreateShader == NULL) return 1;
    glCompileShader = (glCompileShader_TYPE)get_proc_address("glCompileShader");
    if(glCompileShader == NULL) return 1;
    glShaderSource = (glShaderSource_TYPE)get_proc_address("glShaderSource");
    if(glShaderSource == NULL) return 1;
    glGetShaderiv = (glGetShaderiv_TYPE)get_proc_address("glGetShaderiv");
    if(glGetShaderiv == NULL) return 1;
    glDeleteShader = (glDeleteShader_TYPE)get_proc_address("glDeleteShader");
    if(glDeleteShader == NULL) return 1;
    glGetShaderInfoLog = (glGetShaderInfoLog_TYPE)get_proc_address("glGetShaderInfoLog");
    if(glGetShaderInfoLog == NULL) return 1;
    glCreateProgram = (glCreateProgram_TYPE)get_proc_address("glCreateProgram");
    if(glCreateProgram == NULL) return 1;
    glAttachShader = (glAttachShader_TYPE)get_proc_address("glAttachShader");
    if(glAttachShader == NULL) return 1;
    glLinkProgram = (glLinkProgram_TYPE)get_proc_address("glLinkProgram");
    if(glLinkProgram == NULL) return 1;
    glGetProgramiv = (glGetProgramiv_TYPE)get_proc_address("glGetProgramiv");
    if(glGetProgramiv == NULL) return 1;
    glGetProgramInfoLog = (glGetProgramInfoLog_TYPE)get_proc_address("glGetProgramInfoLog");
    if(glGetProgramInfoLog == NULL) return 1;
    glDeleteProgram = (glDeleteProgram_TYPE)get_proc_address("glDeleteProgram");
    if(glDeleteProgram == NULL) return 1;
    glGenBuffers = (glGenBuffers_TYPE)get_proc_address("glGenBuffers");
    if(glGenBuffers == NULL) return 1;
    glBindBuffer = (glBindBuffer_TYPE)get_proc_address("glBindBuffer");
    if(glBindBuffer == NULL) return 1;
    glBufferData = (glBufferData_TYPE)get_proc_address("glBufferData");
    if(glBufferData == NULL) return 1;
    glVertexAttribPointer = (glVertexAttribPointer_TYPE)get_proc_address("glVertexAttribPointer");
    if(glVertexAttribPointer == NULL) return 1;
    glEnableVertexAttribArray = (glEnableVertexAttribArray_TYPE)get_proc_address("glEnableVertexAttribArray");
    if(glEnableVertexAttribArray == NULL) return 1;
    glUseProgram = (glUseProgram_TYPE)get_proc_address("glUseProgram");
    if(glUseProgram == NULL) return 1;
    glGenVertexArrays = (glGenVertexArrays_TYPE)get_proc_address("glGenVertexArrays");
    if(glGenVertexArrays == NULL) return 1;
    glBindVertexArray = (glBindVertexArray_TYPE)get_proc_address("glBindVertexArray");
    if(glBindVertexArray == NULL) return 1;
    glUniformMatrix4fv = (glUniformMatrix4fv_TYPE)get_proc_address("glUniformMatrix4fv");
    if(glUniformMatrix4fv == NULL) return 1;
    glUniform3fv = (glUniform3fv_TYPE)get_proc_address("glUniform3fv");
    if(glUniform3fv == NULL) return 1;
    glUniform1i = (glUniform1i_TYPE)get_proc_address("glUniform1i");
    if(glUniform1i == NULL) return 1;
    glGetUniformLocation = (glGetUniformLocation_TYPE)get_proc_address("glGetUniformLocation");
    if(glGetUniformLocation == NULL) return 1;
    glGetStringi = (glGetStringi_TYPE)get_proc_address("glGetStringi");
    if(glGetStringi == NULL) return 1;
    glGetActiveUniform = (glGetActiveUniform_TYPE)get_proc_address("glGetActiveUniform");
    if(glGetActiveUniform == NULL) return 1;
    glDeleteProgram = (glDeleteProgram_TYPE)get_proc_address("glDeleteProgram");
    if(glDeleteProgram == NULL) return 1;
    glGenerateMipmap = (glGenerateMipmap_TYPE)get_proc_address("glGenerateMipmap");
    if(glGenerateMipmap == NULL) return 1;
    glGetBufferSubData = (glGetBufferSubData_TYPE)get_proc_address("glGetBufferSubData");
    if(glGetBufferSubData == NULL) return 1;
    glDeleteVertexArrays = (glDeleteVertexArrays_TYPE)get_proc_address("glDeleteVertexArrays");
    if(glDeleteVertexArrays == NULL) return 1;
    glDeleteBuffers = (glDeleteBuffers_TYPE)get_proc_address("glDeleteBuffers");
    if(glDeleteBuffers == NULL) return 1;
    return 0;
}

GLExtensions available_gl_extensions = {0};

void check_opengl_extensions(){
    i32 extensions_count;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensions_count);
    for(i32 i = 0; i < extensions_count; i++){
        const unsigned char* extension = glGetStringi(GL_EXTENSIONS, i);
        if(strcmp((char*)extension, "GL_ARB_compute_shader")) available_gl_extensions.GL_ARB_compute_shader_available = 1;
    }
}

#ifdef _WIN32

wglGetExtensionsStringARB_TYPE wglGetExtensionsStringARB;
wglCreateContextAttribsARB_TYPE wglCreateContextAttribsARB;
wglChoosePixelFormatARB_TYPE wglChoosePixelFormatARB;
wglSwapIntervalEXT_TYPE wglSwapIntervalEXT;

WGLExtensions available_wgl_extensions = {0};

u8 load_wgl_functions(){
    if(available_wgl_extensions.WGL_EXT_swap_control_available){
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
u8 opengl_init(i32 opengl_major_version, i32 opengl_minor_version, u32 multisample){
    if(device_context == NULL){
        error("opengl_init: A window is needed for opengl context creation");
        return 1;
    }

    WNDCLASS dummy_class = {0};
    dummy_class.style = CS_OWNDC;
    dummy_class.lpfnWndProc = DefWindowProc;
    dummy_class.hInstance = GetModuleHandle(0);
    dummy_class.lpszClassName = "dummy_window_class";

    if(!RegisterClass(&dummy_class)){
        win32_print_last_error("RegisterClass:");
        return 1;
    }

    HWND dummy_window_handle = CreateWindowEx(0,
        "dummy_window_class",
        "",
        WS_OVERLAPPEDWINDOW,
        0, 0,
        0, 0, NULL, NULL, dummy_class.hInstance, NULL);

    if(!dummy_window_handle){
        win32_print_last_error("CreateWindow:");
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
    u32 dummy_pixel_format_id = ChoosePixelFormat(dummy_device_context, &dummy_pixel_format);

    if(dummy_pixel_format_id == 0){
        error("ChoosePixelFormat: no suitable pixel format found");
        return 1;
    }

    PIXELFORMATDESCRIPTOR good_dummy_pixel_format;
    if(!DescribePixelFormat(dummy_device_context,
                            dummy_pixel_format_id,
                            sizeof(PIXELFORMATDESCRIPTOR),
                            &good_dummy_pixel_format)){
        win32_print_last_error("DescribePixelFormat:");
        return 1;
    }

    if(!SetPixelFormat(dummy_device_context, dummy_pixel_format_id, &good_dummy_pixel_format)){
        win32_print_last_error("SetPixelFormat:");
        return 1;
    }

    HGLRC dummy_opengl_context = wglCreateContext(dummy_device_context);
    if(dummy_opengl_context == NULL){
        win32_print_last_error("wglCreateContext:");
        return 1;
    }

    if(!wglMakeCurrent(dummy_device_context, dummy_opengl_context)){
        win32_print_last_error("wglMakeCurrent:");
        return 1;
    }

    u8 err = 0;

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
            if(str_equals(begin, size, "WGL_ARB_create_context")) available_wgl_extensions.WGL_ARB_create_context_available = 1;
            if(str_equals(begin, size, "WGL_ARB_create_context_profile")) available_wgl_extensions.WGL_ARB_create_context_profile_available = 1;
            if(str_equals(begin, size, "WGL_EXT_swap_control")) available_wgl_extensions.WGL_EXT_swap_control_available  = 1;
            if(str_equals(begin, size, "WGL_ARB_pixel_format")) available_wgl_extensions.WGL_ARB_pixel_format_available  = 1;
        }
        begin = end;
    }

    if(!available_wgl_extensions.WGL_ARB_create_context_available){
        error("WGL_ARB_create_context not available");
        err = 1;
    }
    if(!available_wgl_extensions.WGL_ARB_create_context_profile_available){
        error("WGL_ARB_create_context_profile not available");
        err = 1;
    }
    if(!available_wgl_extensions.WGL_ARB_pixel_format_available){
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
        win32_print_last_error("wglDeleteContext:");
        err = 1;
    }
    if(!ReleaseDC(dummy_window_handle, dummy_device_context)){
        win32_print_last_error("ReleaseDC:");
        err = 1;
    }
    if(!DestroyWindow(dummy_window_handle)){
        win32_print_last_error("DestroyWindow:");
        err = 1;
    }
    if(!UnregisterClass("dummy_window_class", dummy_class.hInstance)){
        win32_print_last_error("UnregisterClass:");
        err = 1;
    }

    if(err) return err;

    i32 pixel_format_attributes[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLES_ARB, multisample,
        0,
    };

    i32 pixel_format;
    u32 num_formats;
    wglChoosePixelFormatARB(device_context, pixel_format_attributes,
                            NULL, 1, &pixel_format, &num_formats);

    PIXELFORMATDESCRIPTOR good_pixel_format;
    if(!DescribePixelFormat(device_context,
                            pixel_format,
                            sizeof(PIXELFORMATDESCRIPTOR),
                            &good_pixel_format)){
        win32_print_last_error("DescribePixelFormat:");
        return 1;
    }

    if(!SetPixelFormat(device_context, pixel_format, &good_pixel_format)){
        win32_print_last_error("SetPixelFormat:");
        return 1;
    }

    i32 context_attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, opengl_major_version,
        WGL_CONTEXT_MINOR_VERSION_ARB, opengl_minor_version,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
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
        win32_print_last_error("wglMakeCurrent:");
        return 1;
    }

    err = load_wgl_functions();
    if(err){
        win32_print_last_error("load_wgl_functions:");
        return 1;
    }

    err = load_opengl_functions();
    if(err){
        win32_print_last_error("load_opengl_functions:");
        return 1;
    }

    i32 major;
    i32 minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    if(major != opengl_major_version || minor != opengl_minor_version){
        warn("Got wrong OpengGL version");
    }

    info("Loaded OpenGL context %d.%d", major, minor);

    check_opengl_extensions();

    return 0;
}

void opengl_swap_buffers(){
    SwapBuffers(device_context);
}

void opengl_set_swap_interval(u32 interval){
    if(wglSwapIntervalEXT == NULL){
        error("opengl_set_swap_interval: wglSwapIntervalEXT isn't available");
        return;
    }
    wglSwapIntervalEXT(interval);
}

#elif __linux__

glXCreateContextAttribsARB_TYPE glXCreateContextAttribsARB;
glXSwapIntervalMESA_TYPE glXSwapIntervalMESA;

GLXExtensions available_glx_extensions = {0};

u8 load_glx_functions(){
    if(available_glx_extensions.GLX_MESA_swap_control_available){
        glXSwapIntervalMESA = (glXSwapIntervalMESA_TYPE)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalMESA");
    }

    return 0;
}

u8 opengl_init(i32 opengl_major_version, i32 opengl_minor_version, u32 multisample){
    i32 glx_major, glx_minor;
    if(!glXQueryVersion(display, &glx_major, &glx_minor) ||
        (glx_major < 1) || (glx_major == 1 && glx_minor < 3)){
        error("opengl_init: GLX version must be at least 1.3");
        return 1;
    }

    const char* glx_extensions_string = glXQueryExtensionsString(display, DefaultScreen(display));
    const char* begin = glx_extensions_string;
    const char* end = begin;
    ptr size;
    while(*begin != '\0'){
        while(*begin == ' ') begin++;
        end = begin;
        while(*end != '\0' && *end != ' ') end++;
        size = end-begin;

        if(size > 0){
            if(str_equals(begin, size, "GLX_ARB_create_context")) available_glx_extensions.GLX_ARB_create_context_available = 1;
            if(str_equals(begin, size, "GLX_ARB_create_context_profile")) available_glx_extensions.GLX_ARB_create_context_profile_available = 1;
            if(str_equals(begin, size, "GLX_MESA_swap_control")) available_glx_extensions.GLX_MESA_swap_control_available = 1;
        }
        begin = end;
    }

    if(!available_glx_extensions.GLX_ARB_create_context_available){
        error("GLX_ARB_create_context not available");
        return 1;
    }

    if(!available_glx_extensions.GLX_ARB_create_context_profile_available){
        error("GLX_ARB_create_context_profile not available");
        return 1;
    }

    i32 visual_attributes[] = {
        GLX_X_RENDERABLE, 1,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_DOUBLEBUFFER, 1,
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_SAMPLES, multisample,
        0
    };

    i32 num_framebuffer_config = 0;
    GLXFBConfig* framebuffer_config = glXChooseFBConfig(display,
                                    DefaultScreen(display), visual_attributes, &num_framebuffer_config);
    if(!framebuffer_config){
        error("glXChooseFBConfig: Failed to get framebuffer config");
        return 1;
    }

    glXCreateContextAttribsARB = (glXCreateContextAttribsARB_TYPE)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    if(glXCreateContextAttribsARB == NULL){
        error("glXCreateContextAttribsARB is NULL");
        return 1;
    }

    const i32 context_attributes[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, opengl_major_version,
        GLX_CONTEXT_MINOR_VERSION_ARB, opengl_minor_version,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    GLXContext opengl_context = glXCreateContextAttribsARB(display, framebuffer_config[0],
                                0, 1, context_attributes);
    XFree(framebuffer_config);
    if(!opengl_context){
        error("glXCreateContextAttribsARB: Failed to create context");
        return 1;
    }

    u8 err = load_glx_functions();
    if(err){
        error("load_glx_functions: Failed to load GLX functions");
        return 1;
    }


    err = load_opengl_functions();
    if(err){
        error("load_opengl_functions: Failed to load OpenGL functions");
        return 1;
    }

    glXMakeCurrent(display, window, opengl_context);

    i32 major;
    i32 minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    info("Loaded OpenGL context %d.%d", major, minor);

    if(major != opengl_major_version || minor != opengl_minor_version){
        warn("Got wrong OpengGL version");
    }

    check_opengl_extensions();

    return 0;
}

void opengl_swap_buffers(){
    glXSwapBuffers(display, window);
}

void opengl_set_swap_interval(u32 interval){
    if(glXSwapIntervalMESA == NULL){
        error("opengl_set_swap_interval: glXSwapIntervalMESA isn't available");
        return;
    }
    glXSwapIntervalMESA(interval);
}

#endif

void opengl_set_viewport(u32 x, u32 y, u32 width, u32 height){
    glViewport(x, y, width, height);
}

void opengl_clear(RGBA clear_color){
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

u32 opengl_load_shader(const char* vertex_shader_filepath, const char* fragment_shader_filepath){
    FILE* vertex_shader_file = fopen(vertex_shader_filepath, "rb");
    FILE* fragment_shader_file = fopen(fragment_shader_filepath, "rb");

    if(vertex_shader_file == NULL){
        error("opengl_load_shader: no such file or directory \"%s\"", vertex_shader_filepath);
        return 0;
    }

    if(fragment_shader_file == NULL){
        error("opengl_load_shader: no such file or directory \"%s\"", fragment_shader_filepath);
        return 0;
    }

    i32 success;
    char info[512];

    char* vertex_shader_text;
    const char* tmp;
    load_file_to_buffer(vertex_shader_file, &vertex_shader_text);
    fclose(vertex_shader_file);
    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    tmp = vertex_shader_text;
    glShaderSource(vertex_shader, 1, &tmp, NULL);
    free(vertex_shader_text);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info);
        error("opengl_load_shader: Failed to compile vertex shader:\n%s", info);
        glDeleteShader(vertex_shader);
        return 0;
    }

    char* fragment_shader_text;
    load_file_to_buffer(fragment_shader_file, &fragment_shader_text);
    fclose(fragment_shader_file);
    u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    tmp = fragment_shader_text;
    glShaderSource(fragment_shader, 1, &tmp, NULL);
    free(fragment_shader_text);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, info);
        error("opengl_load_shader: Failed to compile fragment shader:\n%s", info);
        glDeleteShader(fragment_shader);
        return 0;
    }

    u32 program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, info);
        glDeleteProgram(program);
        error("opengl_load_shader: Failed to link shader program:\n%s", info);
        return 0;
    }

    return program;
}