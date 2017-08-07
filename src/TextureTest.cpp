#include "TextureTest.h"

TextureTest::TextureTest()
{
    // Load Texture data
    GLubyte pixels[] = {
        0xff, 0x00, 0x00, 0xff, // red
        0x00, 0xff, 0x00, 0xff, // green
        0x00, 0x00, 0xff, 0xff, // blue
        0xff, 0xff, 0x00, 0xff, // yellow
    };

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Configure Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Upload Texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // TODO: Generate MipMaps
    // glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind current texture
    glBindTexture(GL_TEXTURE_2D, NO_TEXTURE);
}
