#include <cstdlib>
#include <iostream>

#include "Texture.h"

using std::cerr;
using std::endl;

Texture::Texture() : textureId{0} {
    // Generate Texture Object
    glGenTextures(1, &textureId);
    if (textureId == NO_TEXTURE) {
        cerr << "Unable to generate a new OpenGL texture object." << endl;
        abort();
    }
}

Texture::~Texture() {
    if (textureId != NO_TEXTURE) {
        glDeleteTextures(1, &textureId);
        textureId = NO_TEXTURE;
    }
}

Texture::Texture(Texture&& other) {
    *this = std::move(other);
}

Texture& Texture::operator=(Texture&& other) {
    GLuint temp = textureId;
    textureId = other.textureId;
    other.textureId = temp;
}
