#ifndef __OPENGLINFO_H__
#define __OPENGLINFO_H__

#include <string>
#include <SDL2/SDL_opengles2.h>

class OpenGLInfo {
public:
    OpenGLInfo();
    virtual ~OpenGLInfo() = default;

protected:
    void printString(const std::string& msg, GLenum name);
    void printInt(const std::string& msg, GLenum name);
    void printYesNo(const std::string& msg, GLenum name);
    void printCompressedTextureFormats();
};

#endif // __OPENGLINFO_H__
