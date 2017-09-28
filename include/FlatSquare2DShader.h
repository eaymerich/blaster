#ifndef __FLATSQUARE2DSHADER_H__
#define __FLATSQUARE2DSHADER_H__

#include <Shader.h>


class FlatSquare2DShader : public Shader {
public:
    FlatSquare2DShader();
    virtual ~FlatSquare2DShader() = default;
    virtual void setPosition(const GLfloat* position) const;
    virtual void setColor(const GLfloat* color) const;
    virtual void setSize(const GLfloat* size) const;
    virtual void setOffset(const GLfloat* offset) const;

protected:
    GLint sizeIndex;
    GLint offsetIndex;
    GLint positionIndex;
    GLint colorIndex;
};

#endif // __FLATSQUARE2DSHADER_H__
