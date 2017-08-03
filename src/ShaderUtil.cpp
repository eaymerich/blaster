#include <cstdlib>
#include <iostream>
#include <fstream>

#include "ShaderUtil.h"

using std::cerr;
using std::endl;
using std::ifstream;
using std::ios;
using std::streampos;
using std::string;
using std::vector;

ShaderUtil::ShaderUtil() {
}

GLint ShaderUtil::loadProgram(string name) {
    // Read Shader sources
    auto vs_source = readFromFile("./shaders/" + name + ".vert");
    auto fs_source = readFromFile("./shaders/" + name + ".frag");

    // Create and compile shaders
    auto vertexShader = getShader(vs_source.data(), GL_VERTEX_SHADER);
    auto fragmentShader = getShader(fs_source.data(), GL_FRAGMENT_SHADER);

    // Create program and link shaders to it
    auto programId = getProgram(vertexShader, fragmentShader);

    return programId;
}

vector<char> ShaderUtil::readFromFile(const string& filename) {
    ifstream file{filename, ios::in | ios::binary | ios::ate};
    if (!file.is_open()) {
        cerr << "Couldn't open file: " << filename << endl;
        abort();
    }
    streampos filesize = file.tellg();
    vector<char> buffer;
    buffer.resize(filesize + streampos{1});
    file.seekg(0, ios::beg);
    file.read(buffer.data(), filesize);
    file.close();
    buffer[filesize] = 0;
    return buffer;
}

GLuint ShaderUtil::getShader(const char* shaderSrc, GLenum type) {
    // Create Shader
    auto shader = glCreateShader(type);
    if (shader == 0){
        cerr << "ERROR: could not create GLSL shader." << endl;
        abort();
    }

    // Compile Shader
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    // Check compile status
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled){
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 0){
            vector<char> infoLog;
            infoLog.resize(infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog.data());
            cerr << "Error compiling shader:" << endl
                 << infoLog.data() << endl;
        }
        glDeleteShader(shader);
        abort();
    }

    return shader;
}

GLint ShaderUtil::getProgram(GLuint vertexShaderId, GLuint fragmentShaderId) {
    // Create program
    auto programObject = glCreateProgram();
    if(programObject == 0){
        cerr << "ERROR: could not create GLSL program." << endl;
        abort();
    }

    // Attach shaders and link
    glAttachShader(programObject, vertexShaderId);
    glAttachShader(programObject, fragmentShaderId);
    glLinkProgram(programObject);

    // Check link status
    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if(!linked){
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1){
            vector<char> infoLog;
            infoLog.resize(infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog.data());
            cerr << "ERROR linking GLSL program:" << endl
                 << infoLog.data() << endl;
        }
        glDeleteProgram(programObject);
        abort();
    }
    return programObject;
}
