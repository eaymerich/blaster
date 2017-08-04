#ifndef __TEXTUREDSQUARE_H__
#define __TEXTUREDSQUARE_H__

#include <GLES2/gl2.h>

class TexturedSquare {
public:
    TexturedSquare();
    virtual ~TexturedSquare();
    virtual void draw();

protected:
    static GLfloat vertices[];
    static GLfloat textureCoordinates[];
    GLint program;
    GLint positionIndex;
    GLint textureCoordinateIndex;
    GLint textureUnitIndex;
    GLuint textureId;
};

#endif // __TEXTUREDSQUARE_H__
