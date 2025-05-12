#include <ctime>

#include "Tests.h"
#include "FULLGAME.h"

int main() {

    srand(time(nullptr));
    Tests tests;
    FULLGAME Game;
    Game.RunGame(15,15);

    return 0;
}
