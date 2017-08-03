#include <cstdlib>
#include <iostream>

#include "ShaderUtil.h"
#include "SimpleSquare.h"

using std::cout;
using std::cerr;
using std::endl;
using std::abort;

GLfloat SimpleSquare::vertices[] = {
    // Front face
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f
};

SimpleSquare::SimpleSquare() {
    ShaderUtil util;
    program = util.loadProgram("simple");
    positionIndex = glGetAttribLocation(program, "position");
}

SimpleSquare::~SimpleSquare() {
}

void SimpleSquare::draw() {
    glUseProgram(program);

    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionIndex);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
