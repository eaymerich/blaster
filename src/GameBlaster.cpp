#include <iostream>

#include "GameBlaster.h"

using std::cout;
using std::endl;

GameBlaster::GameBlaster() {
    cout << "===== Game Blaster Info =====" << endl;
    cout << "Game Start" << endl;
}

GameBlaster::~GameBlaster() {
    cout << "Game Over" << endl;
}

void GameBlaster::start() {
}
