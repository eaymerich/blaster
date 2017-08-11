#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

#include "TextureAlpha.h"
#include "FileUtil.h"

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
using std::equal;
using std::string;
using std::vector;

TextureAlpha::TextureAlpha(string filename) {
    cout << "TextureAlpha()" << endl;
    if (endsWith(filename, ".pf")) {
        loadFromPf(filename);
    } else {
        cerr << "Unable to load texture: unknown extension: "
             << filename << endl;
        abort();
    }
}

// TextureAlpha::TextureAlpha(const TextureAlpha& other) {
//     textureId = other.textureId;
// }

TextureAlpha::~TextureAlpha() {
    cout << "~TextureAlpha()" << endl;
}

/**
 * Load texture from a PixelFont file (.pf).
 */
void TextureAlpha::loadFromPf(string filename) {
    auto buffer = FileUtil::read("./textures/" + filename);

    if (buffer.size() < PF_FILESIZE) {
        cerr << filename << " has an incorrect size: " << buffer.size()
             << ", should be " << PF_FILESIZE << endl;
        abort();
    }
    //GLfloat pixels[PF_PIXELS_TOTAL];
    vector<char> pixels;
    pixels.resize(PF_PIXELS_TOTAL);
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
                    pixels[pixelOffset] = value ?
                        PF_FOREGROUND_COLOR : PF_BACKGROUND_COLOR;
                    pixelOffset++;
                }

                // Go to next line of pixel buffer
                pixelOffsetStart += PF_PIXELS_PER_LINE;
            }
        }
    }

    loadFromPixels(pixels.data(), PF_PIXELS_PER_LINE, PF_PIXELS_PER_LINE);
}

void TextureAlpha::loadFromPixels(char* data, GLsizei width, GLsizei height) {
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Configure Texture Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Upload Texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0,
                 GL_ALPHA, GL_UNSIGNED_BYTE, data);

    // Generate MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind current texture
    glBindTexture(GL_TEXTURE_2D, NO_TEXTURE);
}

bool TextureAlpha::endsWith(string value, string ending) {
    return ending.size() <= value.size() &&
        equal(ending.rbegin(), ending.rend(), value.rbegin());
}
