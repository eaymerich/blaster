#include "PixelCharLine.h"

using std::move;
using std::string;
using std::vector;

PixelCharLine::PixelCharLine(const string& line, float ratio):
    zPos{0.0f} {

    float xScale = 1.0f / HALF_CHARS_PER_LINE / ratio;
    float yScale = 1.0f / HALF_CHARS_PER_LINE;

    mLine.reserve(line.size());

    float xPos = 0.0f;
    float xOffset = xScale;
    for (const char& c : line) {
        PixelChar pc;
        pc.setChar(c);
        pc.setScale(xScale, yScale);
        pc.setPosition(xPos, 0.0f, 0.0f);
        //pc.setForegoundColor(1.0f, 1.0f, 0.0f, 1.0f);
        pc.setBackgoundColor(0.0f, 0.0f, 0.0f, 0.0f);
        xPos += xOffset;
        mLine.push_back(move(pc));
    }
}

PixelCharLine::PixelCharLine(const PixelCharLine& other) : Element2D() {
    *this = other;
}

PixelCharLine::PixelCharLine(PixelCharLine&& other) {
    *this = move(other);
}

PixelCharLine& PixelCharLine::operator=(const PixelCharLine& other) {
    mLine = other.mLine;
    position[0] = other.position[0];
    position[1] = other.position[1];
    zPos = other.zPos;
    return *this;
}

PixelCharLine& PixelCharLine::operator=(PixelCharLine&& other) {
    mLine.swap(other.mLine);
    position[0] = other.position[0];
    position[1] = other.position[1];
    zPos = other.zPos;
    return *this;
}

void PixelCharLine::draw(
    float xModelPos, float yModelPos, float zModelPos) const {

    for(const auto& pixelChar : mLine) {
        pixelChar.draw(xModelPos + position[0],
                       yModelPos + position[1],
                       zModelPos + zPos);
    }
}

void PixelCharLine::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    zPos = z;
}
