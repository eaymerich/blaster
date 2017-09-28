#include "DrawContext.h"
#include "Display2D.h"

Display2D::Display2D() :
    width{0},
    height{0},
    xOffset{0},
    yOffset{0} {

    unsigned int w, h;
    DrawContext::getDrawSize(w, h);
    width = w;
    height = h;

    if (width > height) { // Landscape mode
        xOffset = (width - height) / 2;
        minSize = height;
    } else { // Portait or square mode
        yOffset = (height - width) / 2;
        minSize = width;
    }
}

Display2D::~Display2D() {
    elements.clear();
}

void Display2D::draw() const {
    // Set viewport for a square display
    glViewport(xOffset, yOffset, minSize, minSize);

    // Disable depth test
    glDisable(GL_DEPTH_TEST);

    // Draw all 2D elements
    for(const auto& element : elements) {
        element->draw();
    }

    // Reenable depth test
    glEnable(GL_DEPTH_TEST);

    // Restore viewport
    glViewport(0,0, width, height);
}

void Display2D::add(Element2D* element) {
    elements.insert(elements.end(), element);
}

void Display2D::remove(Element2D* element) {
    elements.remove(element);
}
