#ifndef DEFAULTCOMP_H
#define DEFAULTCOMP_H
#include "Player.h"

class DefaultComputer : public Player { // ConcreteElementB
    public:
        // makeMove returns d for print deck, r for ragequit, and 0 otherwise
        char makeMove(Game &game) override;

        explicit DefaultComputer(unsigned int score); // : Player{score} {}
};

#endif