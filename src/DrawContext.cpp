#include <cstdlib>
#include <iostream>

#include "DrawContext.h"
#include "OpenGLInfo.h"

using std::cout;
using std::cerr;
using std::endl;
using std::abort;

DrawContext* DrawContext::uniqueDrawContex = nullptr;

DrawContext::DrawContext() :
    width{1024},
    height{768} {

    initSDL();
    printSDLInfo();
    initEGL();
    printEGLInfo();
    configOpenGLES20();
    printOpenGLInfo();

    // If everything went OK, set this as the unique DrawContext
    uniqueDrawContex = this;
}

DrawContext::~DrawContext() {

    // Destroy EGL stuff
    if (surface) {
        eglDestroySurface(display, surface);
        surface = nullptr;
    }
    if (context) {
        eglDestroyContext(display, context);
        context = nullptr;
    }
    if (display) {
        eglTerminate(display);
        display = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    // Destroy SDL stuff
    if (window){
        SDL_DestroyWindow(window);
        window = nullptr;
        nativeWindow = nullptr;
    }
    SDL_Quit();

    // Remove the unique DrawContext
    if (uniqueDrawContex == this) {
        uniqueDrawContex = nullptr;
    }
}

void DrawContext::initSDL() {
    // Init SDL
    if (SDL_Init(0) < 0) {
        throw std::runtime_error(std::string{"SDL not initialized: "} +
                                 SDL_GetError());
    }

    // Create window
    window = SDL_CreateWindow("Blaster!",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
                              //SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        throw std::runtime_error(std::string{"Window not created: "} +
                                 SDL_GetError());
    }

    // Get native Window handler (needed to init EGL later on...)
    SDL_SysWMinfo window_info = {};
    SDL_VERSION(&window_info.version);
    if (!SDL_GetWindowWMInfo(window, &window_info)) {
        throw std::runtime_error(
            "SDL Unable to get WindowWM information.");
    }

    #if defined(SDL_VIDEO_DRIVER_X11)
        nativeWindow = window_info.info.x11.window;
    #elif defined(SDL_VIDEO_DRIVER_WINDOWS)
        nativeWindow = window_info.info.win.window;
    #elif
        #error Unable to get a native window handler!
    #endif
}

void DrawContext::initEGL() {
    // Get an EGL display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        throw std::runtime_error("Unable to get an EGL Display!");
    }

    // Initialize Display
    if (!eglInitialize(display, nullptr, nullptr)) {
        throw std::runtime_error("Unable to initialize the Display!");
    }

    // Use OpenGL ES API
    eglBindAPI(EGL_OPENGL_ES_API);

    // Choose EGL frame buffer configuration
    EGLint attribute_list[] = {
        EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };
    EGLConfig config = {};
    EGLint num_config{0};
    if (!eglChooseConfig(display,
                         attribute_list,
                         &config,
                         1,
                         &num_config)) {
        throw std::runtime_error(
            "Unable to find a suitable EGL frame buffer configuration!");
    }

    // Create an OpenGL ES 2.0 rendering context
    EGLint context_attrib[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    context = eglCreateContext(display,
                               config,
                               EGL_NO_CONTEXT,
                               context_attrib);
    if (context == EGL_NO_CONTEXT) {
        throw std::runtime_error(
            "Unable to create OpenGL ES 2.0 rendering context!");
    }

    // Create a Native Window (already done by SDL :D )

    // Create an EGL Surface
    surface = eglCreateWindowSurface(display, config, nativeWindow, nullptr);
    if (surface == EGL_NO_SURFACE) {
        throw std::runtime_error("Unable to create a window Surface!");
    }
    eglMakeCurrent(display, surface, surface, context);
}

void DrawContext::configOpenGLES20() {
    glFrontFace(GL_CCW); // Set triangle orientation as counter-clock wise.
    glCullFace(GL_BACK), // Cull triangles looking away from camera.
    glEnable(GL_CULL_FACE); // Activate triangle culling.
    glEnable(GL_DEPTH_TEST); // Activate depth test.
    glDepthFunc(GL_LEQUAL); // Set Depth function.
    glEnable(GL_BLEND); // Activate Alpha blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearDepthf(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void DrawContext::printSDLInfo() {
    // Print Platform Info
    cout << "===== SDL Info =====" << endl;
    SDL_version version;
    SDL_GetVersion(&version);
    cout << "Version: " << (uint32_t)version.major << "."
                        << (uint32_t)version.minor << "."
                        << (uint32_t)version.patch << endl;
    cout << "Platform: " << SDL_GetPlatform() << endl;
    cout << "Logical CPU count: " << SDL_GetCPUCount() << endl;
    cout << "Total amount of RAM: " << SDL_GetSystemRAM() << "MB" << endl;
    cout << endl;
}

void DrawContext::printEGLInfo() {
    cout << "===== EGL Info =====" << endl;
    auto vendor = eglQueryString(display, EGL_VENDOR);
    cout << "EGL Vendor: " << vendor << endl;
    auto version = eglQueryString(display, EGL_VERSION);
    cout << "EGL Version: " << version << endl;
    auto clients = eglQueryString(display, EGL_CLIENT_APIS);
    cout << "EGL Client APIs: " << clients << endl;
    cout << endl;
}

void DrawContext::printOpenGLInfo() {
    OpenGLInfo glInfo{};
}

void DrawContext::swap() {
    eglSwapBuffers(display, surface);
}

void DrawContext::getDrawSize(unsigned int& w, unsigned int& h) {
    if (uniqueDrawContex) {
        w = uniqueDrawContex->width;
        h = uniqueDrawContex->height;
    }
}
