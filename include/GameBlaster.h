#ifndef __GAMEBLASTER_H__
#define __GAMEBLASTER_H__

#include "DrawContext.h"

class GameBlaster {
public:
    GameBlaster();
    virtual ~GameBlaster();
    virtual void start();

protected:
    DrawContext drawContex;
};

#endif // __GAMEBLASTER_H__
