#include "ShaderManager.h"
#include "DefaultShapes.h"

#include "FlatSquare2D.h"

using DefaultShapes::Square;

FlatSquare2D::FlatSquare2D() :
    color{0.0f, 0.0f, 0.0f, 1.0f},
    program{ShaderManager::getFlatSquare2DShader()} {
}

void FlatSquare2D::setColor(float r, float g, float b, float a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

void FlatSquare2D::draw() const {
    program->useProgram();

    // Set uniforms
    program->setSize(size);
    program->setOffset(position);
    program->setColor(color);

    // Set attributes
    program->setPosition(Square::position);

    // Draw
    glDrawArrays(Square::mode, 0, Square::size);
}
