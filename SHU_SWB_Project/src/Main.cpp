/***************************************************************************************
*	Title: Main.cpp
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#include <Windows.h>
#include "Game/GameApplication.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {

    GameApplication game;

    if (game.initialize()) {
        game.run();
    }

    return 0;
}
