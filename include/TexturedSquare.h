#ifndef __TEXTUREDSQUARE_H__
#define __TEXTUREDSQUARE_H__

#include <GLES2/gl2.h>

class TexturedSquare {
public:
    TexturedSquare(GLuint tex);
    virtual ~TexturedSquare() = default;
    virtual void draw();

protected:
    static GLfloat vertices[];
    static GLfloat textureCoordinates[];
    GLint program;
    GLint positionIndex;
    GLint textureCoordinateIndex;
    GLint textureUnitIndex;
    const GLuint texture;
};

#endif // __TEXTUREDSQUARE_H__
