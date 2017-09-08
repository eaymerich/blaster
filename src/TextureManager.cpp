#include <cstdlib>
#include <iostream>

#include "FileUtil.h"
#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#define PF_FILESIZE 2048
#define PF_CHARS_PER_LINE 16
#define PF_CHARS_PER_COLUMN 16
#define PF_PIXELS_PER_CHAR 8
#define PF_PIXELS_PER_LINE (PF_PIXELS_PER_CHAR * PF_CHARS_PER_LINE)
#define PF_PIXELS_TOTAL (PF_PIXELS_PER_LINE * PF_PIXELS_PER_LINE)
#define PF_FOREGROUND_COLOR 0xff
#define PF_BACKGROUND_COLOR 0x00

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

TextureManager* TextureManager::UniqueTextureManager = nullptr;

TextureManager::TextureManager() {
    cout << "TextureManager()" << endl;
    // Set this TextureManager as the Unique
    UniqueTextureManager = this;
}

TextureManager::~TextureManager() {
    cout << "~TextureManager()" << endl;

    // Delete Textures
    for (const auto& element : textureAlphaBank) {
        glDeleteTextures(1, &(element.second));
    }
    textureAlphaBank.clear();

    for (const auto& element : textureRGBABank) {
        glDeleteTextures(1, &(element.second));
    }
    textureRGBABank.clear();

    // Remove this TextureManager as the Unique
    if (UniqueTextureManager == this){
        UniqueTextureManager = nullptr;
    }
}

GLuint TextureManager::getTextureAlpha(const string& filename) {
    return UniqueTextureManager->_getTextureAlpha(filename);
}

GLuint TextureManager::_getTextureAlpha(const string& filename) {
    auto element = textureAlphaBank.find(filename);
    if (element != textureAlphaBank.end()) {
        // Texture is already loaded
        return element->second;
    }
    // We need to load texture from file
    GLuint texId = generateNewTextureId();
    loadAlphaTexture(texId, filename);
    textureAlphaBank[filename] = texId;
    return texId;
}

GLuint TextureManager::getTextureRGBA(const string& filename) {
    return UniqueTextureManager->_getTextureRGBA(filename);
}

GLuint TextureManager::_getTextureRGBA(const string& filename) {
    auto element = textureRGBABank.find(filename);
    if (element != textureRGBABank.end()) {
        // Texture is already loaded
        return element->second;
    }
    // We need to load texture from file
    GLuint texId = generateNewTextureId();
    loadRGBATexture(texId, filename);
    textureRGBABank[filename] = texId;
    return texId;
}

GLuint TextureManager::generateNewTextureId() {
    GLuint textureId;
    glGenTextures(1, &textureId);
    if (textureId == NO_TEXTURE) {
        cerr << "Unable to generate a new OpenGL texture object." << endl;
        abort();
    }
    return textureId;
}

void TextureManager::loadAlphaTexture(
    GLuint textureId, const string& filename) {

    // Read pixels
    PixelData pixels;
    if (FileUtil::hasExtension(filename, ".pf")) {
        readPixelsFromPf(filename, pixels);
    } else {
        cerr << "Unable to load texture: unknown extension: "
             << filename << endl;
        abort();
    }

    if (pixels.channels != 1) {
        cerr << "Error loading AlphaTexture: file " << filename
             << " has wrong number of channels: " << pixels.channels << endl;
        abort();
    }

    uploadTextureToGPU(textureId, pixels, GL_ALPHA);
}

void TextureManager::loadRGBATexture(
    GLuint textureId, const std::string& filename) {

    // Read pixels
    PixelData pixels;
    if (FileUtil::hasExtension(filename, ".png")) {
        readPixelsFromPng(filename, pixels);
    } else {
        cerr << "Unable to load texture: unknown extension: "
             << filename << endl;
        abort();
    }

    if (pixels.channels != 4) {
        cerr << "Error loading RGBA Texture: file " << filename
             << " has wrong number of channels: " << pixels.channels << endl;
        abort();
    }

    uploadTextureToGPU(textureId, pixels, GL_RGBA);
}

void TextureManager::uploadTextureToGPU(
    GLuint textureId, const PixelData& pixels, GLenum format) {

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Configure Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Upload Texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, pixels.width, pixels.height, 0,
                 format, GL_UNSIGNED_BYTE, pixels.pixels.data());

    // Generate MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind current texture
    glBindTexture(GL_TEXTURE_2D, NO_TEXTURE);
}

/**
 * Load pixel data from a PixelFont file (.pf).
 */
void TextureManager::readPixelsFromPf(
    const string& filename, PixelData& data) {

    // Read data from file
    auto buffer = FileUtil::read("./textures/" + filename);
    if (buffer.size() < PF_FILESIZE) {
        cerr << filename << " has an incorrect size: " << buffer.size()
             << ", should be " << PF_FILESIZE << endl;
        abort();
    }

    // Initialize pixel data
    data.pixels.resize(PF_PIXELS_TOTAL);
    data.width = PF_PIXELS_PER_LINE;
    data.height = PF_PIXELS_PER_LINE;
    data.channels = 1;

    // Convert data from file into pixels
    size_t bufferOffset = 0;
    for (int y = 0; y < PF_CHARS_PER_COLUMN; y++) {
        for (int x = 0; x < PF_CHARS_PER_LINE; x++) {
            size_t pixelOffsetStart =
                (y * PF_PIXELS_PER_LINE * PF_PIXELS_PER_CHAR) +
                (x * PF_PIXELS_PER_CHAR);

            // Read one PixelFont char, i.e.:
            // read 8 lines of one PixelFont char
            for (int i = 0; i < 8; i++) {
                // Read one line of this PixelFont char
                char line = buffer[bufferOffset++];

                // Convert line to pixel values
                size_t pixelOffset = pixelOffsetStart;
                for (unsigned char mask = 0x80; mask != 0; mask >>= 1) {
                    char value = line & mask;
                    data.pixels[pixelOffset] = value ?
                        PF_FOREGROUND_COLOR : PF_BACKGROUND_COLOR;
                    pixelOffset++;
                }

                // Go to next line of pixel buffer
                pixelOffsetStart += PF_PIXELS_PER_LINE;
            }
        }
    }
}

/**
 * Load pixel data from a PNG file (.png).
 */
void TextureManager::readPixelsFromPng(
    const string& filename, PixelData& data) {

    // Read data from file
    unsigned char* buffer = stbi_load(("./textures/" + filename).c_str(),
        &(data.width), &(data.height), &(data.channels), 0);

    // Copy pixels to PixelData
    unsigned int bufferSize = data.width * data.height * data.channels;
    data.pixels.reserve(bufferSize);
    for (unsigned int i = 0; i < bufferSize; i++) {
        data.pixels[i] = buffer[i];
    }

    // Release buffer
    stbi_image_free(buffer);
}
