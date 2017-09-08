#ifndef __ELEMENT2D_H__
#define __ELEMENT2D_H__

#include <GLES2/gl2.h>

class Element2D {
public:
    Element2D(float x = 0.0f,
              float y = 0.0f,
              float width = 1.0f,
              float height = 1.0f);
    virtual ~Element2D() = default;
    virtual void draw() const = 0;

protected:
    float xPos;
    float yPos;
    float wSize;
    float hSize;
};

#endif // __ELEMENT2D_H__
