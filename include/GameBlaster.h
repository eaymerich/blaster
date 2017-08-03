#ifndef __GAMEBLASTER_H__
#define __GAMEBLASTER_H__

#include "EventHandler.h"
#include "DrawContext.h"
#include "GoOn.h"
#include "InputManager.h"

class GameBlaster : public EventHandler {
public:
    GameBlaster();
    virtual ~GameBlaster();
    virtual void start();
    virtual void handleExit() override;
    virtual void handleKeyDown(
        SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) override;
protected:
    GoOn goOn;
    InputManager inputManager;
    DrawContext drawContex;
};

#endif // __GAMEBLASTER_H__
