#ifndef __DEFAULTSHAPES_H__
#define __DEFAULTSHAPES_H__

#include <GLES2/gl2.h>

namespace DefaultShapes {

class Square {
public:
    virtual ~Square() = default;
    static GLfloat position[];
    static GLenum mode;
    static GLsizei size;
private:
    Square() = default;
};

} // namespace DefaultShapes

#endif // __DEFAULTSHAPES_H__
