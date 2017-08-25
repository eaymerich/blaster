#ifndef __PIXELCHARLINE_H__
#define __PIXELCHARLINE_H__

#include <string>
#include <vector>
#include <GLES2/gl2.h>

#include "PixelChar.h"

#define CHARS_PER_LINE (40)
#define HALF_CHARS_PER_LINE (CHARS_PER_LINE / 2)

class PixelCharLine {
public:
    PixelCharLine(const std::string& line = "", float ratio = 1.0f);
    PixelCharLine(const PixelCharLine& other);
    PixelCharLine(PixelCharLine&& other);
    virtual ~PixelCharLine() = default;
    virtual PixelCharLine& operator=(const PixelCharLine& other);
    virtual PixelCharLine& operator=(PixelCharLine&& other);
    virtual void draw(float xModelPos = 0.0f,
                      float yModelPos = 0.0f,
                      float zModelPos = 0.0f) const;
    virtual void setPosition(float x, float y, float z);

protected:
    std::vector<PixelChar> mLine;
    float xPos, yPos, zPos;
};

#endif // __PIXELCHARLINE_H__
