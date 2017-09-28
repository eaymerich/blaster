#include "GameHUD.h"

GameHUD::GameHUD() :
    scoreText{"SCORE"},
    lifeText{"LIFE"} {

    float charWidth = 2.0f / CHARS_PER_LINE;
    scoreText.setPosition(-(charWidth * 18.0f), -(charWidth * 15.0f), 0.0f);
    lifeText.setPosition(-(charWidth * 2.0f), -(charWidth * 15.0f), 0.0f);

    background.setSize(2.0f, 0.3f);
    background.setPosition(0.0f, -0.85f);
    background.setColor(0.1f, 0.1f, 0.9f);

    // Add elements to display
    display.add(&background);
    display.add(&scoreText);
    display.add(&lifeText);
}

GameHUD::~GameHUD() {
}

void GameHUD::draw() const {
    display.draw();
}
