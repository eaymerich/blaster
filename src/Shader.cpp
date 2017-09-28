#include "Shader.h"

Shader::Shader() :
    program{0} {
}

Shader::~Shader()
{
    if (program != 0) {
        glDeleteProgram(program);
        program = 0;
    }
}
