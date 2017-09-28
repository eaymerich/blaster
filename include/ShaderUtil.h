#ifndef __SHADERUTIL_H__
#define __SHADERUTIL_H__

#include <vector>
#include <string>
#include <SDL2/SDL_opengles2.h>

class ShaderUtil {
public:
    ShaderUtil() = default;
    virtual ~ShaderUtil() = default;
    static GLuint loadProgram(const std::string& name);
protected:
    static std::vector<char> readFromFile(const std::string& filename);
    static GLuint getShader(const char* shaderSrc, GLenum type);
    static GLuint getProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
};

#endif // __SHADERUTIL_H__
