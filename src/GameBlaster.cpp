#include <iostream>

#include "GameBlaster.h"
#include "SimpleSquare.h"
#include "TexturedSquare.h"

using std::cout;
using std::endl;

GameBlaster::GameBlaster() {
    cout << "===== Game Blaster Info =====" << endl;
    cout << "Game Start" << endl;
    inputManager.setEventHandler(this);
}

GameBlaster::~GameBlaster() {
    cout << "Game Over" << endl;
}

void GameBlaster::start() {
    TexturedSquare square;

    while(goOn) {
        // Read Input
        inputManager.readInput();

        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw objects
        square.draw();

        // Update screen
        drawContex.swap();

        // Wait for not consumming all CPU
        SDL_Delay(15);
    }
}

void GameBlaster::handleExit() {
    goOn.stop();
}

void GameBlaster::handleKeyDown(
    SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) {
    (void)(scancode);
    (void)(mod);

    if (sym == SDLK_ESCAPE) {
        goOn.stop();
    }
}
