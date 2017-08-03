#ifndef __PIXELFONT_H__
#define __PIXELFONT_H__

#define FONT_ARRAY_SIZE 2048

#include <stdint.h>

class PixelFont {
public:
    PixelFont();
    virtual ~PixelFont() = default;
    virtual unsigned char* getTexture();
    virtual uint32_t getTextureSize();

private:
static unsigned char font[FONT_ARRAY_SIZE];

};

#endif // __PIXELFONT_H__
