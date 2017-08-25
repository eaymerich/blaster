#include "PixelCharBox.h"

using std::move;
using std::string;

PixelCharBox::PixelCharBox() :
    xPos{0.0f}, yPos{0.0f}, zPos{0.0f} {
}

void PixelCharBox::setText(std::string text, float ratio) {
    float yPos = 0.0f;
    float yOffset = PixelCharBox::yOffset();
    unsigned int pos = 0;
    string sLine = text.substr(pos, CHARS_PER_LINE);
    while (sLine != "") {
        PixelCharLine pcLine(sLine, ratio);
        pcLine.setPosition(0.0f, yPos, 0.0f);
        mLines.push_back(move(pcLine));

        pos += CHARS_PER_LINE;
        sLine = text.substr(pos, CHARS_PER_LINE);
        yPos -= yOffset;
    }
}

void PixelCharBox::draw(
    float xModelPos, float yModelPos, float zModelPos) const {

    for (const auto& line : mLines) {
        line.draw(xModelPos + xPos, yModelPos + yPos, zModelPos + zPos);
    }
}

void PixelCharBox::setPosition(float x, float y, float z) {
    xPos = x;
    yPos = y;
    zPos = z;
}

float PixelCharBox::xCentered(float ratio) {
    return -((HALF_CHARS_PER_LINE - 0.5f) *
             (1.0f / HALF_CHARS_PER_LINE / ratio));
}

float PixelCharBox::yOffset() {
    return (1.0f / HALF_CHARS_PER_LINE) * 1.2f;
}
