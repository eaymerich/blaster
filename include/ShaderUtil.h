#ifndef __SHADERUTIL_H__
#define __SHADERUTIL_H__

#include <vector>
#include <string>
#include <SDL2/SDL_opengles2.h>

class ShaderUtil {
public:
    ShaderUtil();
    virtual ~ShaderUtil() = default;
    virtual GLint loadProgram(std::string name);
protected:
    virtual std::vector<char> readFromFile(const std::string& filename);
    virtual GLuint getShader(const char* shaderSrc, GLenum type);
    virtual GLint getProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
};

#endif // __SHADERUTIL_H__
