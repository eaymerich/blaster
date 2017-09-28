#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__

#include <memory>
#include <string>
#include <unordered_map>
#include <GLES2/gl2.h>

#include "FlatSquare2DShader.h"


class ShaderManager {
public:
    ShaderManager();
    virtual ~ShaderManager();
    static GLuint getProgram(const std::string& programName);
    static FlatSquare2DShader* getFlatSquare2DShader();

protected:
    GLuint _getProgram(const std::string& programName);
    FlatSquare2DShader* _getFlatSquare2DShader();

    static ShaderManager* uniqueShaderManager;
    std::unordered_map<std::string, GLuint> shaderBank;

    std::unique_ptr<FlatSquare2DShader> flatSquare2DShader;
};

#endif // __SHADERMANAGER_H__
