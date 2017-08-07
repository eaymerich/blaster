#ifndef __TEXTUREDSQUARE_H__
#define __TEXTUREDSQUARE_H__

#include <GLES2/gl2.h>

#include "Texture.h"

class TexturedSquare {
public:
    TexturedSquare(const Texture& tex);
    virtual ~TexturedSquare() = default;
    virtual void draw();

protected:
    static GLfloat vertices[];
    static GLfloat textureCoordinates[];
    GLint program;
    GLint positionIndex;
    GLint textureCoordinateIndex;
    GLint textureUnitIndex;
    const Texture& texture;
};

#endif // __TEXTUREDSQUARE_H__
