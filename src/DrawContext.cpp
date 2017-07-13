#include <cstdlib>
#include <iostream>

#include "DrawContext.h"

using std::cerr;
using std::endl;
using std::abort;

DrawContext::DrawContext() :
    window{nullptr},
    glcontext{0},
    width{1024},
    height{768} {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize: " << SDL_GetError() << endl;
        abort();
    }

    window = SDL_CreateWindow("SDL Test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );//| SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        cerr << "Window could not be created: " << SDL_GetError() << endl;
        abort();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(0); // 0 - vsync off   1 - vsync on
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glcontext = SDL_GL_CreateContext(window);

    glFrontFace(GL_CCW); // Set triangle orientation as counter-clock wise.
    glCullFace(GL_BACK), // Cull triangles looking away from camera.
               glEnable(GL_CULL_FACE); // Activate triangle culling.
    glEnable(GL_DEPTH_TEST); // Activate depth test.
    glDepthFunc(GL_LEQUAL);
    glClearDepthf(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

DrawContext::~DrawContext() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DrawContext::swap() {
    SDL_GL_SwapWindow(window);
}
