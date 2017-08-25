#ifndef __PIXELCHAR_H__
#define __PIXELCHAR_H__

#include <GLES2/gl2.h>

class PixelChar {
public:
    PixelChar();
    PixelChar(const PixelChar& other);
    PixelChar(PixelChar&& other);
    virtual ~PixelChar();
    virtual PixelChar& operator=(const PixelChar& other);
    virtual PixelChar& operator=(PixelChar&& other);
    virtual void draw(float xModelPos = 0.0f,
                      float yModelPos = 0.0f,
                      float zModelPos = 0.0f) const;
    virtual void setChar(char c);
    virtual void setPosition(float x, float y, float z);
    virtual void setScale(float sx, float sy);
    virtual void setForegoundColor(float r, float g, float b, float a);
    virtual void setBackgoundColor(float r, float g, float b, float a);

protected:
    static GLfloat vertices[];
    static GLfloat textureCoordinates[];
    static GLfloat xTextureOffset[];
    static GLfloat yTextureOffset[];
    static unsigned int pixelCharCount;
    static GLint program;
    static GLint scaleIndex;
    static GLint positionIndex;
    static GLint positionOffsetIndex;
    static GLint textureCoordinateIndex;
    static GLint textureOffsetIndex;
    static GLint textureUnitIndex;
    static GLint foregroundColorIndex;
    static GLint backgroundColorIndex;
    static GLuint texture;

    char pChar;
    GLfloat xOffset, yOffset, zOffset;
    GLfloat xScale, yScale;
    GLfloat fgR, fgG, fgB, fgA;
    GLfloat bgR, bgG, bgB, bgA;

    void calculateOffsets();
};

#endif // __PIXELCHAR_H__
