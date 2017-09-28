#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

#include "ShaderUtil.h"
#include "ShaderManager.h"

using std::string;
using std::make_unique;

ShaderManager* ShaderManager::uniqueShaderManager = nullptr;

ShaderManager::ShaderManager() :
    flatSquare2DShader{nullptr} {
    // Set this shader manager as the unique
    uniqueShaderManager = this;
}

ShaderManager::~ShaderManager() {
    // Delete all loaded shaders
    for(const auto& program : shaderBank) {
        glDeleteProgram(program.second);
    }
    shaderBank.clear();

    // Remove this shader manager as the unique
    if (uniqueShaderManager == this){
        uniqueShaderManager = nullptr;
    }
}

GLuint ShaderManager::getProgram(const string& programName) {
    return uniqueShaderManager->_getProgram(programName);
}

GLuint ShaderManager::_getProgram(const string& programName) {
    auto element = shaderBank.find(programName);
    if (element != shaderBank.end()) {
        // Shader is already loaded
        return element->second;
    }

    // Load and save shader
    cout << "Loading shader \"" << programName << "\"" << endl;
    auto program = ShaderUtil::loadProgram(programName);
    shaderBank[programName] = program;

    GLint attributes = 0;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &attributes);
    cout << "\tAttributes: " << attributes << endl;

    GLint attributeNameLength = 0;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
                   &attributeNameLength);
    vector<GLchar> attributeName;
    attributeName.reserve(attributeNameLength);
    GLsizei alegth;
    GLint asize;
    GLenum atype;
    glGetActiveAttrib(program,0,attributeNameLength,
                      &alegth, &asize, &atype, attributeName.data());
    string name{attributeName.data()};
    cout << "\t\t - " << name << endl;

    GLint uniforms = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniforms);
    cout << "\tUniforms: " << uniforms << endl;

    return program;
}

FlatSquare2DShader* ShaderManager::getFlatSquare2DShader() {
    return uniqueShaderManager->_getFlatSquare2DShader();
}

FlatSquare2DShader* ShaderManager::_getFlatSquare2DShader() {
    if (!flatSquare2DShader) {
        flatSquare2DShader = make_unique<FlatSquare2DShader>();
    }
    return flatSquare2DShader.get();
}
