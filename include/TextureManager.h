#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#include <GLES2/gl2.h>

#define NO_TEXTURE 0

struct PixelData {
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
    static GLuint getTextureRGBA(const std::string& filename);
protected:
    GLuint _getTextureAlpha(const std::string& filename);
    GLuint _getTextureRGBA(const std::string& filename);
    GLuint generateNewTextureId();
    void loadAlphaTexture(GLuint textureId, const std::string& filename);
    void loadRGBATexture(GLuint textureId, const std::string& filename);
    void uploadTextureToGPU(
        GLuint textureId,
        const PixelData& pixels,
        GLenum format);
    void readPixelsFromPf(const std::string& filename, PixelData& data);
    void readPixelsFromPng(const std::string& filename, PixelData& data);
    static TextureManager* UniqueTextureManager;
    std::unordered_map<std::string, GLuint> textureAlphaBank;
    std::unordered_map<std::string, GLuint> textureRGBABank;
};

#endif // __TEXTUREMANAGER_H__
