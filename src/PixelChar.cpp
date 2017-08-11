#include "PixelChar.h"
#include "TextureManager.h"
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

unsigned int PixelChar::pixelCharCount = 0;
GLint PixelChar::program = 0;
GLint PixelChar::positionIndex = -1;
GLint PixelChar::textureCoordinateIndex = -1;
GLint PixelChar::textureUnitIndex = -1;
GLuint PixelChar::texture = NO_TEXTURE;

PixelChar::PixelChar() {
    if (pixelCharCount == 0) {
        // Load texture
        if (texture == NO_TEXTURE) {
            texture = TextureManager::getTextureAlpha("pixelfont.pf");
        }

        // Load shader
        ShaderUtil util;
        program = util.loadProgram("pixelchar");
        positionIndex = glGetAttribLocation(program, "aPosition");
        textureCoordinateIndex =
            glGetAttribLocation(program, "aTextureCoordinate");
        textureUnitIndex = glGetUniformLocation(program, "uTextureUnit");
    }
    pixelCharCount++;
}

PixelChar::~PixelChar() {
    pixelCharCount--;
    if (pixelCharCount == 0){
        glDeleteProgram(program);
        program = 0;
        positionIndex = -1;
        textureCoordinateIndex = -1;
        textureUnitIndex = -1;
        texture = NO_TEXTURE;
    }
}

void PixelChar::draw() {
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

