#include "Human.h"
using namespace std;


Human::Human(unsigned int score) : Player{score} {}

// makeMove returns d for print deck, r for ragequit, and 0 otherwise
char Human::makeMove(Game &game) {
    return game.visit(this);
}
