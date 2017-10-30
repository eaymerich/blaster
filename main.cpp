#include <iostream>
#include "GameBlaster.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    cout << "GameBlaster v0.1" << endl;
    try {
        GameBlaster game;
        game.start();
    } catch (const std::exception& e){
        std::cerr << e.what() << endl;
    }
    return 0;
}
