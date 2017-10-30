#ifndef __DRAWCONTEXT_H__
#define __DRAWCONTEXT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

class DrawContext {
public:
    DrawContext();
    virtual ~DrawContext();
    virtual void swap();
    static void getDrawSize(unsigned int& w, unsigned int& h);

private:
    void initSDL();
    void initEGL();
    void configOpenGLES20();
    void printSDLInfo();
    void printEGLInfo();
    void printOpenGLInfo();

    static DrawContext* uniqueDrawContex;
    GLsizei width;
    GLsizei height;
    SDL_Window* window{nullptr};
    NativeWindowType nativeWindow{0};
    EGLDisplay display{nullptr};
    EGLContext context{nullptr};
    EGLSurface surface{nullptr};
};

#endif // __DRAWCONTEXT_H__
