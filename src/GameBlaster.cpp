#include <iostream>

#include "GameBlaster.h"
#include "SimpleSquare.h"
#include "TexturedSquare.h"
#include "TextureTest.h"
#include "TextureAlpha.h"
#include "TextureManager.h"
#include "PixelChar.h"
#include "PixelCharLine.h"
#include "PixelCharBox.h"
#include "GameHUD.h"
#include "ShaderManager.h"

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

    TextureManager texManager;
    ShaderManager shaderManager;

    float ratio = 1024.0f / 768.0f;
    //TextureTest texture;
    //TexturedSquare square{TextureManager::getTextureRGBA("mouse01.png")};

    //PixelChar mChar;
    //mChar.setChar('g');
    //PixelCharLine charLine{"Hello World!"};
    //PixelCharLine charLine{"1234567890123456789012345678901234567890", 1024.0f / 768.0f};
    PixelCharBox box;
    box.setText("1234567890123456789012345678901234567890"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ12345678901234"
                "abcedfghijklmnopqrstuvwxyz12345678901234",
                ratio);
    box.setPosition(PixelCharBox::xCentered(ratio),
                    PixelCharBox::yOffset() * -3.5f, 0.0f);

    GameHUD hud;

    while(goOn) {
        // Read Input
        inputManager.readInput();

        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw objects
        hud.draw();
        //square.draw();
        //box.draw();

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
