#include "PixelCharLine.h"

using std::move;
using std::string;
using std::vector;

PixelCharLine::PixelCharLine(const string& line, float ratio):
    xPos{0.0f}, yPos{0.0f}, zPos{0.0f} {

    float xScale = 1.0f / HALF_CHARS_PER_LINE / ratio;
    float yScale = 1.0f / HALF_CHARS_PER_LINE;

    mLine.reserve(line.size());

    //float xPos = -((HALF_CHARS_PER_LINE - 0.5f) * xScale);
    float xPos = 0.0f;
    float xOffset = xScale;
    for (const char& c : line) {
        PixelChar pc;
        pc.setChar(c);
        pc.setScale(xScale, yScale);
        pc.setPosition(xPos, 0.0f, 0.0f);
        //pc.setForegoundColor(1.0f, 1.0f, 0.0f, 1.0f);
        //pc.setBackgoundColor(0.0f, 0.0f, 1.0f, 0.0f);
        xPos += xOffset;
        mLine.push_back(move(pc));
    }
}

PixelCharLine::PixelCharLine(const PixelCharLine& other) {
    *this = other;
}

PixelCharLine::PixelCharLine(PixelCharLine&& other) {
    *this = move(other);
}

PixelCharLine& PixelCharLine::operator=(const PixelCharLine& other) {
    mLine = other.mLine;
    xPos = other.xPos;
    yPos = other.yPos;
    zPos = other.zPos;
    return *this;
}

PixelCharLine& PixelCharLine::operator=(PixelCharLine&& other) {
    mLine.swap(other.mLine);
    xPos = other.xPos;
    yPos = other.yPos;
    zPos = other.zPos;
    return *this;
}

void PixelCharLine::draw(
    float xModelPos, float yModelPos, float zModelPos) const {

    for(const auto& pixelChar : mLine) {
        pixelChar.draw(xModelPos + xPos, yModelPos + yPos, zModelPos + zPos);
    }
}

void PixelCharLine::setPosition(float x, float y, float z) {
    xPos = x;
    yPos = y;
    zPos = z;
}
