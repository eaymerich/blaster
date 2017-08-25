#include <iostream>

#include "PixelChar.h"
#include "TextureManager.h"
#include "ShaderUtil.h"

#define CHAR_COLS 16
#define CHAR_ROWS 16
#define CHAR_WIDTH (1.0f / CHAR_COLS)
#define CHAR_HEIGHT (1.0f / CHAR_ROWS)

using std::move;
using std::cout;
using std::endl;

GLfloat PixelChar::vertices[] = {
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f
};

GLfloat PixelChar::textureCoordinates[] = {
    0.0f,        0.0f,
    0.0f,        CHAR_WIDTH,
    CHAR_HEIGHT, CHAR_WIDTH,
    CHAR_HEIGHT, 0.0f
};

GLfloat PixelChar::xTextureOffset[256] = {0.0f};
GLfloat PixelChar::yTextureOffset[256] = {0.0f};

unsigned int PixelChar::pixelCharCount = 0;
GLint PixelChar::program = 0;
GLint PixelChar::scaleIndex = -1;
GLint PixelChar::positionIndex = -1;
GLint PixelChar::positionOffsetIndex = -1;
GLint PixelChar::textureCoordinateIndex = -1;
GLint PixelChar::textureOffsetIndex = -1;
GLint PixelChar::textureUnitIndex = -1;
GLint PixelChar::foregroundColorIndex = -1;
GLint PixelChar::backgroundColorIndex = -1;
GLuint PixelChar::texture = NO_TEXTURE;

PixelChar::PixelChar() :
    pChar{'A'},
    xOffset{0.0f}, yOffset{0.0f}, zOffset{0.0f},
    xScale{1.0f}, yScale{1.0f},
    fgR{1.0f}, fgG{1.0f}, fgB{1.0f}, fgA{1.0f},
    bgR{0.0f}, bgG{0.0f}, bgB{0.0f}, bgA{1.0f} {

    if (pixelCharCount == 0) {
        cout << "Loading resources for PixelChar..." << endl;

        calculateOffsets();

        // Load texture
        if (texture == NO_TEXTURE) {
            texture = TextureManager::getTextureAlpha("pixelfont.pf");
        }

        // Load shader
        ShaderUtil util;
        program = util.loadProgram("pixelchar");

        // Get attribute indexes
        positionIndex = glGetAttribLocation(program, "aPosition");
        textureCoordinateIndex =
            glGetAttribLocation(program, "aTextureCoordinate");

        // Get uniform indexes
        scaleIndex = glGetUniformLocation(program, "uScale");
        textureOffsetIndex = glGetUniformLocation(program, "uTextureOffset");
        textureUnitIndex = glGetUniformLocation(program, "uTextureUnit");
        positionOffsetIndex = glGetUniformLocation(program, "uPositionOffset");
        foregroundColorIndex =
            glGetUniformLocation(program, "uForegroundColor");
        backgroundColorIndex =
            glGetUniformLocation(program, "uBackgroundColor");
    }
    pixelCharCount++;
}

PixelChar::PixelChar(const PixelChar& other) {
    *this = other;
    pixelCharCount++;
}

PixelChar::PixelChar(PixelChar&& other) {
    *this = move(other);
    pixelCharCount++;
}

PixelChar::~PixelChar() {
    pixelCharCount--;
    if (pixelCharCount == 0){
        cout << "Freeing resources for PixelChar..." << endl;
        glDeleteProgram(program);
        program = 0;
        scaleIndex = -1;
        positionIndex = -1;
        textureCoordinateIndex = -1;
        textureOffsetIndex = -1;
        textureUnitIndex = -1;
        positionOffsetIndex = -1;
        foregroundColorIndex = -1;
        backgroundColorIndex = -1;
        texture = NO_TEXTURE;
    }
}

PixelChar& PixelChar::operator=(const PixelChar& other) {
    pChar = other.pChar;
    xOffset = other.xOffset;
    yOffset = other.yOffset;
    zOffset = other.zOffset;
    xScale = other.xScale;
    yScale = other.yScale;
    fgR = other.fgR;
    fgG = other.fgG;
    fgB = other.fgB;
    fgA = other.fgA;
    bgR = other.bgR;
    bgG = other.bgG;
    bgB = other.bgB;
    bgA = other.bgA;

    return *this;
}

PixelChar& PixelChar::operator=(PixelChar&& other) {
    *this = other;
    return *this;
}

void PixelChar::calculateOffsets() {
    // Fill X offset
    int i = 0;
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            xTextureOffset[i++] = CHAR_WIDTH * x;
        }
    }

    // Fill Y offset
    i = 0;
    for (int y = 0; y < 16; y++) {
        GLfloat yOff = CHAR_HEIGHT * y;
        for (int x = 0; x < 16; x++) {
            yTextureOffset[i++] = yOff;
        }
    }
}

void PixelChar::draw(float xModelPos, float yModelPos, float zModelPos) const {
    glUseProgram(program);

    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionIndex);

    glVertexAttribPointer(textureCoordinateIndex, 2, GL_FLOAT, GL_FALSE, 0,
                          textureCoordinates);
    glEnableVertexAttribArray(textureCoordinateIndex);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureUnitIndex, 0);

    glUniform2f(textureOffsetIndex, xTextureOffset[(unsigned char)pChar],
                                    yTextureOffset[(unsigned char)pChar]);
    glUniform2f(scaleIndex, xScale, yScale);

    glUniform3f(positionOffsetIndex,
                xModelPos + xOffset,
                yModelPos + yOffset,
                zModelPos + zOffset);

    glUniform4f(foregroundColorIndex, fgR, fgG, fgB, fgA);
    glUniform4f(backgroundColorIndex, bgR, bgG, bgB, bgA);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void PixelChar::setChar(char c) {
    pChar = c;
}

void PixelChar::setPosition(float x, float y, float z) {
    xOffset = x;
    yOffset = y;
    zOffset = z;
}

void PixelChar::setScale(float sx, float sy) {
    xScale = sx;
    yScale = sy;
}

void PixelChar::setForegoundColor(float r, float g, float b, float a) {
    fgR = r;
    fgG = g;
    fgB = b;
    fgA = a;
}

void PixelChar::setBackgoundColor(float r, float g, float b, float a) {
    bgR = r;
    bgG = g;
    bgB = b;
    bgA = a;
}
