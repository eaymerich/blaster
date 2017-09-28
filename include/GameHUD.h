#ifndef __GAMEHUD_H__
#define __GAMEHUD_H__

#include "Display2D.h"
#include "PixelCharLine.h"
#include "FlatSquare2D.h"

class GameHUD {
public:
    GameHUD();
    virtual ~GameHUD();
    virtual void draw() const;

protected:
    Display2D display;
    PixelCharLine scoreText;
    PixelCharLine lifeText;
    FlatSquare2D background;
};

#endif // __GAMEHUD_H__
