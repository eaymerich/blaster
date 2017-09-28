#include "Element2D.h"

Element2D::Element2D(float x, float y, float width, float height) :
    position{x, y},
    size{width, height} {
}

void Element2D::setPosition(float x, float y) {
    position[0] = x;
    position[1] = y;
}

void Element2D::setSize(float width, float height) {
    size[0] = width;
    size[1] = height;
}
