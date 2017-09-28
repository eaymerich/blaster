#include "ShaderUtil.h"
#include "FlatSquare2DShader.h"


FlatSquare2DShader::FlatSquare2DShader() {
    program = ShaderUtil::loadProgram("flatsquare2d");

    // Query attribute index
    positionIndex = glGetAttribLocation(program, "aPosition");

    // Query uniform index
    sizeIndex = glGetUniformLocation(program, "uSize");
    offsetIndex = glGetUniformLocation(program, "uOffset");
    colorIndex = glGetUniformLocation(program, "uColor");
}

void FlatSquare2DShader::setPosition(const GLfloat* position) const {
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, position);
    glEnableVertexAttribArray(positionIndex);
}

void FlatSquare2DShader::setColor(const GLfloat* color) const {
    glUniform4fv(colorIndex, 1, color);
}

void FlatSquare2DShader::setSize(const GLfloat* size) const {
    glUniform2fv(sizeIndex, 1, size);
}

void FlatSquare2DShader::setOffset(const GLfloat* offset) const {
    glUniform2fv(offsetIndex, 1, offset);
}
