#ifndef __PIXELCHAR_H__
#define __PIXELCHAR_H__

#include <GLES2/gl2.h>

#include "TextureAlpha.h"

class PixelChar {
public:
    PixelChar();
    virtual ~PixelChar();
    virtual void draw();

protected:
    static GLfloat vertices[];
    static GLfloat textureCoordinates[];
    GLint program;
    GLint positionIndex;
    GLint textureCoordinateIndex;
    GLint textureUnitIndex;
    const TextureAlpha texture;
};

#endif // __PIXELCHAR_H__
