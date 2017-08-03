#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "EventHandler.h"

class InputManager
{
public:
    InputManager();
    virtual ~InputManager() = default;
    virtual void readInput();
    virtual void setEventHandler(EventHandler* handler);
private:
    EventHandler* eventHandler;
};

#endif // __INPUTMANAGER_H__
