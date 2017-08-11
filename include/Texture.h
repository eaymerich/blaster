#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GLES2/gl2.h>

#define NO_TEXTURE 0

class Texture {
public:
    Texture();
    virtual ~Texture();
    // Make Texture non copyable
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    // Make Texture movable
    Texture(Texture&& other);
    Texture& operator=(Texture&& other);

    virtual GLuint getId() const {
        return textureId;
    }

protected:
    GLuint textureId;
};

#endif // __TEXTURE_H__
