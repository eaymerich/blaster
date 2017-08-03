#include <SDL2/SDL.h>

#include "InputManager.h"

InputManager::InputManager() :
    eventHandler{nullptr}
{}

void InputManager::setEventHandler(EventHandler* handler) {
    eventHandler = handler;
}

void InputManager::readInput() {
    SDL_Event event;
    if (eventHandler) {
        while (SDL_PollEvent(&event)) {
            eventHandler->handleEvent(&event);
        }
    }
}
