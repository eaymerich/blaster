#ifndef __PIXELCHARBOX_H__
#define __PIXELCHARBOX_H__

#include <string>
#include <vector>

#include "PixelCharLine.h"

class PixelCharBox {
public:
    PixelCharBox();
    virtual ~PixelCharBox() = default;
    virtual void draw(float xModelPos = 0.0f,
                      float yModelPos = 0.0f,
                      float zModelPos = 0.0f) const;
    virtual void setText(std::string text, float ratio = 1.0f);
    virtual void setPosition(float x, float y, float z);
    static float xCentered(float ratio);
    static float yOffset();

protected:
    std::vector<PixelCharLine> mLines;
    float xPos, yPos, zPos;
};

#endif // __PIXELCHARBOX_H__
