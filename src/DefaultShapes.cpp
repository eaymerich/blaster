#include "DefaultShapes.h"

using namespace DefaultShapes;


/* Square data */

GLfloat Square::position[] = {
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f
};

GLenum Square::mode = GL_TRIANGLE_FAN;

GLsizei Square::size = 4;
