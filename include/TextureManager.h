#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#include <GLES2/gl2.h>

#define NO_TEXTURE 0

struct PixelData {
    PixelData() {std::cout << "PixelData()" << std::endl;}
    ~PixelData() {std::cout << "~PixelData()" << std::endl;}
    GLsizei width = 0;
    GLsizei height = 0;
    GLsizei channels = 0;
    std::vector<GLubyte> pixels;
};

class TextureManager {
public:
    TextureManager();
    virtual ~TextureManager();
    static GLuint getTextureAlpha(const std::string& filename);
protected:
    GLuint _getTextureAlpha(const std::string& filename);
    GLuint generateNewTextureId();
    void loadAlphaTexture(GLuint textureId, const std::string& filename);
    void readPixelsFromPf(const std::string& filename, PixelData& data);
    static TextureManager* UniqueTextureManager;
    std::unordered_map<std::string, GLuint> textureAlphaBank;
};

#endif // __TEXTUREMANAGER_H__
