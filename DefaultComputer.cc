#include "DefaultComputer.h"
using namespace std;

DefaultComputer::DefaultComputer(unsigned int score) : Player{score} {}

// makeMove returns d for print deck, r for ragequit, and 0 otherwise
char DefaultComputer::makeMove(Game &game) {
    return game.visit(this);
}
