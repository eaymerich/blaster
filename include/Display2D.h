#ifndef __DISPLAY2D_H__
#define __DISPLAY2D_H__

#include <list>
#include <GLES2/gl2.h>

#include "Element2D.h"

class Display2D {
public:
    Display2D();
    virtual ~Display2D();
    virtual void draw();
    virtual void add(Element2D* element);
    virtual void remove(Element2D* element);

protected:
    std::list<Element2D*> elements;
    GLsizei width;
    GLsizei height;
    GLsizei minSize;
    GLint xOffset;
    GLint yOffset;
};

#endif // __DISPLAY2D_H__
