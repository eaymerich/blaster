#ifndef __PIXELCHAR_H__
#define __PIXELCHAR_H__

#include <GLES2/gl2.h>

class PixelChar {
public:
    PixelChar();
    virtual ~PixelChar();
    virtual void draw();

protected:
    static GLfloat vertices[];
    static GLfloat textureCoordinates[];
    static unsigned int pixelCharCount;
    static GLint program;
    static GLint positionIndex;
    static GLint textureCoordinateIndex;
    static GLint textureUnitIndex;
    static GLuint texture;
};

#endif // __PIXELCHAR_H__
