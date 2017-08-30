#include <cstdlib>
#include <iostream>

#include "TexturedSquare.h"
#include "ShaderUtil.h"

using std::cerr;
using std::endl;

GLfloat TexturedSquare::vertices[] = {
    // Front face
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f
};

GLfloat TexturedSquare::textureCoordinates[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

TexturedSquare::TexturedSquare(GLuint tex) :
    texture{tex} {

    ShaderUtil util;
    program = util.loadProgram("textured");

    // Get attribute index
    positionIndex = glGetAttribLocation(program, "aPosition");
    textureCoordinateIndex =
        glGetAttribLocation(program, "aTextureCoordinate");

    // Get Uniform index
    textureUnitIndex = glGetUniformLocation(program, "uTextureUnit");
}

void TexturedSquare::draw() {
    glUseProgram(program);

    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionIndex);

    glVertexAttribPointer(textureCoordinateIndex, 2, GL_FLOAT, GL_FALSE, 0,
                          textureCoordinates);
    glEnableVertexAttribArray(textureCoordinateIndex);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureUnitIndex, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
