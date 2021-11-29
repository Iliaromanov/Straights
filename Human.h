#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"

class Human : public Player { // ConcreteElementA
    public:
        // makeMove returns d for print deck, r for ragequit, and 0 otherwise
        char makeMove(Game &game) override;
};

#endif