#ifndef TEXTUREALPHA_H
#define TEXTUREALPHA_H

#include <string>

#include <Texture.h>


class TextureAlpha : public Texture {
public:
    TextureAlpha(std::string filename);
    virtual ~TextureAlpha() = default;

protected:
    void loadFromPf(std::string filename);
    void loadFromPixels(char* data, GLsizei width, GLsizei height);
    bool endsWith(std::string value, std::string ending);
};

#endif // TEXTUREALPHA_H
