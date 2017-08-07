#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GLES2/gl2.h>

#define NO_TEXTURE 0

class Texture {
public:
    Texture();
    virtual ~Texture();
    virtual GLuint getId() const {
        return textureId;
    }

protected:
    GLuint textureId;
};

#endif // __TEXTURE_H__
