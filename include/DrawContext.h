#ifndef __DRAWCONTEXT_H__
#define __DRAWCONTEXT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>

class DrawContext {
public:
    DrawContext();
    virtual ~DrawContext();
    virtual void swap();
    static void getDrawSize(unsigned int& w, unsigned int& h);

private:
    static DrawContext* uniqueDrawContex;
    SDL_Window* window;
    SDL_GLContext glcontext;
    GLsizei width;
    GLsizei height;
};

#endif // __DRAWCONTEXT_H__
