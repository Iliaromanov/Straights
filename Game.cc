#include "Game.h"
using namespace std;


Game::Game(unsigned int turnNum) : turnNum{turnNum} {} // ctor
Game::~Game() {} // dtor

// updates turnNum
void Game::nextTurn() {
    ++turnNum;
    if (turnNum == 4) turnNum = 0;
}
int Game::getTurnNum(){ return turnNum; } // getter