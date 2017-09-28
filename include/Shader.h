#ifndef __SHADER_H__
#define __SHADER_H__

#include <GLES2/gl2.h>


class Shader {
public:
    virtual ~Shader();
    void useProgram() const {
        glUseProgram(program);
    }

protected:
    Shader();

    GLuint program;
};

#endif // __SHADER_H__
