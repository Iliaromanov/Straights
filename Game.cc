#include "Game.h"
using namespace std;


Game::Game(unsigned int turnNum) : turnNum{turnNum}, turnCount{1} {} // ctor
Game::~Game() {} // dtor

// updates turnNum
void Game::nextTurn() {
    ++turnCount;
    ++turnNum;
    if (turnNum == 4) turnNum = 0;
}

// getters
int Game::getTurnNum(){ return turnNum; }
int Game::getTurnCount(){ return turnCount; } 