#include "PixelChar.h"
#include "ShaderUtil.h"

GLfloat PixelChar::vertices[] = {
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f
};

GLfloat PixelChar::textureCoordinates[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

PixelChar::PixelChar() : texture{"pixelfont.pf"} {
    ShaderUtil util;
    program = util.loadProgram("pixelchar");
    positionIndex = glGetAttribLocation(program, "aPosition");
    textureCoordinateIndex =
        glGetAttribLocation(program, "aTextureCoordinate");
    textureUnitIndex = glGetUniformLocation(program, "uTextureUnit");
}

PixelChar::~PixelChar() {
}

void PixelChar::draw() {
    glUseProgram(program);

    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionIndex);

    glVertexAttribPointer(textureCoordinateIndex, 2, GL_FLOAT, GL_FALSE, 0,
                          textureCoordinates);
    glEnableVertexAttribArray(textureCoordinateIndex);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getId());
    glUniform1i(textureUnitIndex, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

