#include <iostream>
#include <vector>

#if __has_include(<GLES3/gl3.h>)
# include <GLES3/gl3.h>
#endif // __has_include(<GLES3/gl3.h>)

#include "OpenGLInfo.h"

using std::vector;
using std::string;
using std::cerr;
using std::cout;
using std::endl;

OpenGLInfo::OpenGLInfo()
{
    cout << "===== OpenGL ES Info =====" << endl;
    printString("Vendor", GL_VENDOR);
    printString("Renderer", GL_RENDERER);
    printString("Version", GL_VERSION);
    printString("Shading Language Version", GL_SHADING_LANGUAGE_VERSION);
    printInt("Sample Buffers", GL_SAMPLE_BUFFERS);
    // printCompressedTextureFormats();
    printInt("Max Texture size: ", GL_MAX_TEXTURE_SIZE);
    printInt("Max CubeMap Texture size: ", GL_MAX_CUBE_MAP_TEXTURE_SIZE);
    printInt("Max Texture Units: ", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
    printInt("Max Texture Units in Vertex Shader: ",
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
    printInt("Max Texture Units in Fragment Shader: ",
        GL_MAX_TEXTURE_IMAGE_UNITS);
    printInt("Max Uniforms in Vertex Shader: ",
        GL_MAX_VERTEX_UNIFORM_VECTORS);
    printInt("Max Uniforms in Fragment Shader: ",
        GL_MAX_FRAGMENT_UNIFORM_VECTORS);
    printInt("Max Attribs in Vertex Shader: ", GL_MAX_VERTEX_ATTRIBS);
    printInt("Max Varying variables: ", GL_MAX_VARYING_VECTORS);
    printYesNo("Shader Compiler Support: ", GL_SHADER_COMPILER);
    // printString("Extensions", GL_EXTENSIONS);
    cout << endl;
}

void OpenGLInfo::printString(const string& msg, GLenum name) {
    auto val = glGetString(name);
    if (val == 0) {
        string msg{"Error getting GL string: "};
        string err;
        switch (glGetError()) {
        case GL_NO_ERROR:
            err = "GL_NO_ERROR";
            break;
        case GL_INVALID_ENUM:
            err = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            err = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            err = "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            err = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            err = "GL_OUT_OF_MEMORY";
            break;
        default:
            err = "Unknown error";
        }
        throw std::runtime_error(msg + err);
    }
    cout << msg << ": " << (char*)val << endl;
}

void OpenGLInfo::printInt(const std::string& msg, GLenum name) {
    GLint val = 0;
    glGetIntegerv(name, &val);
    cout << msg << ": " << val << endl;
}

void OpenGLInfo::printYesNo(const std::string& msg, GLenum name) {
    GLboolean val = GL_FALSE;
    glGetBooleanv(name, &val);
    cout << msg << ": ";
    if (val == GL_TRUE) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    cout << endl;
}

void OpenGLInfo::printCompressedTextureFormats() {
    GLint num = 0;
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &num);

    vector<GLint> formats;
    formats.resize(num);
    glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats.data());

    cout << "Supported compressed texture formats: " << num << endl;
    for (auto& format : formats) {
        cout << "   ";
        switch(format){
        case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
            cout << "GL_COMPRESSED_RGB_S3TC_DXT1_EXT";
            break;
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
            cout << "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT";
            break;
        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
            cout << "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT";
            break;
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
            cout << "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT";
            break;
        case GL_ETC1_RGB8_OES:
            cout << "GL_ETC1_RGB8_OES";
            break;
#ifdef GL_ES_VERSION_3_0
        case GL_COMPRESSED_R11_EAC:
            cout << "GL_COMPRESSED_R11_EAC (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_SIGNED_R11_EAC:
            cout << "GL_COMPRESSED_SIGNED_R11_EAC (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_RG11_EAC:
            cout << "GL_COMPRESSED_RG11_EAC (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_SIGNED_RG11_EAC:
            cout << "GL_COMPRESSED_SIGNED_RG11_EAC (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_RGB8_ETC2:
            cout << "GL_COMPRESSED_RGB8_ETC2 (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_SRGB8_ETC2:
            cout << "GL_COMPRESSED_SRGB8_ETC2 (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
            cout << "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 "
                    "(OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
            cout << "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 "
                    "(OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_RGBA8_ETC2_EAC:
            cout << "GL_COMPRESSED_RGBA8_ETC2_EAC (OpenGL ES 3.0)";
            break;
        case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
            cout << "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC (OpenGL ES 3.0)";
            break;
#endif // GL_ES_VERSION_3_0
        default:
            cout << "Unknown compressed texture format: 0x"
                 << std::hex << format << std::dec;
            break;
        }
        cout << endl;
    }
}
