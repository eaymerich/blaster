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

TexturedSquare::TexturedSquare() {
    ShaderUtil util;
    program = util.loadProgram("textured");
    positionIndex = glGetAttribLocation(program, "aPosition");
    textureCoordinateIndex =
        glGetAttribLocation(program, "aTextureCoordinate");
    textureUnitIndex = glGetUniformLocation(program, "uTextureUnit");

    // Texture Stuff
    GLubyte myTexture[] = {
        0xff, 0x00, 0x00, 0xff, // red
        0x00, 0xff, 0x00, 0xff, // green
        0x00, 0x00, 0xff, 0xff, // blue
        0xff, 0xff, 0x00, 0xff, // yellow
    };

    // Generate Texture Object
    glGenTextures(1, &textureId);
    if (textureId == 0) {
        cerr << "Unable to generate a new OpenGL texture object." << endl;
        abort();
    }

    // Use generated texture object
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Configure Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Upload Texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, myTexture);

    // TODO: Generate MipMaps
    // glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind current texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

TexturedSquare::~TexturedSquare() {
    glDeleteTextures(1, &textureId);
}

void TexturedSquare::draw() {
    glUseProgram(program);

    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionIndex);

    glVertexAttribPointer(textureCoordinateIndex, 2, GL_FLOAT, GL_FALSE, 0,
                          textureCoordinates);
    glEnableVertexAttribArray(textureCoordinateIndex);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(textureUnitIndex, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
