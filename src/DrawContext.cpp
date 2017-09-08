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
    window{nullptr},
    glcontext{0},
    width{1024},
    height{768} {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL not initialized: " << SDL_GetError() << endl;
        abort();
    }

    // Set OpenGL ES 2.0 Profile
    // Note: this must be done before creating any window.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // TODO: Disable this flag in release version.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    // Set OpenGL ES Attributes
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    window = SDL_CreateWindow("Blaster!",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);//| SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        cerr << "Window not created: " << SDL_GetError() << endl;
        abort();
    }

    // Set Vertical Sync
    SDL_GL_SetSwapInterval(0); // 0 - vsync off   1 - vsync on

    glcontext = SDL_GL_CreateContext(window);

    // Print Platform Info
    cout << "===== Platform Info =====" << endl;
    cout << "Platform: " << SDL_GetPlatform() << endl;
    cout << "Logical CPU count: " << SDL_GetCPUCount() << endl;
    cout << "Total amount of RAM: " << SDL_GetSystemRAM() << "MB" << endl;

    int win_width = 0;
    int win_height = 0;
    SDL_GL_GetDrawableSize(window, &win_width, &win_height);
    cout << "Window size: " << win_width << "x" << win_height << endl;
    width = win_width;
    height = win_height;

    int multisample = 0;
    int samples = 0;
    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &multisample);
    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &samples);
    cout << "Multisampling: " << multisample << endl;
    cout << "Samples: " << samples << endl;
    cout << endl;

    // Print OpenGL ES information
    OpenGLInfo glInfo;

    // Configure OpenGL ES
    glFrontFace(GL_CCW); // Set triangle orientation as counter-clock wise.
    glCullFace(GL_BACK), // Cull triangles looking away from camera.
    glEnable(GL_CULL_FACE); // Activate triangle culling.
    glEnable(GL_DEPTH_TEST); // Activate depth test.
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND); // Activate Alpha blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearDepthf(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // If everything went OK, set this as the unique DrawContext
    uniqueDrawContex = this;
}

DrawContext::~DrawContext() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if (uniqueDrawContex == this) {
        uniqueDrawContex = nullptr;
    }
}

void DrawContext::swap() {
    SDL_GL_SwapWindow(window);
}

void DrawContext::getDrawSize(unsigned int& w, unsigned int& h) {
    w = uniqueDrawContex->width;
    h = uniqueDrawContex->height;
}
