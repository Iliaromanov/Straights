#ifndef STDGAME_H
#define STDGAME_H
#include "Game.h"
#include <vector>

class Card;

class StandardGame : public Game {
    std::vector<std::vector<Card *>> piles;
    void visit(Human *human) override;
    void visit(DefaultComputer *comp) override;
};

#endif