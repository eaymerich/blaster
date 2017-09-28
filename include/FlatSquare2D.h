#ifndef __FLATSQUARE2D_H__
#define __FLATSQUARE2D_H__

#include <GLES2/gl2.h>

#include "Element2D.h"
#include "FlatSquare2DShader.h"

class FlatSquare2D : public Element2D {
public:
    FlatSquare2D();
    virtual ~FlatSquare2D() = default;
    virtual void setColor(float r, float g, float b, float a = 1.0f);
    virtual void draw() const override;

protected:
    float color[4];
    FlatSquare2DShader* program;
};

#endif // __FLATSQUARE2D_H__
