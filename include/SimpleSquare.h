#ifndef __SIMPLESQUARE_H__
#define __SIMPLESQUARE_H__

#include <GLES2/gl2.h>

class SimpleSquare
{
public:
    SimpleSquare();
    virtual ~SimpleSquare();
    virtual void draw();

protected:
    static GLfloat vertices[];

    GLint program;
    GLint positionIndex;
};

#endif // __SIMPLESQUARE_H__
