#ifndef STDGAME_H
#define STDGAME_H
#include "Game.h"
#include <memory>
#include <map>
#include <vector>

class Player;
class Card;

class StandardGame : public Game {
    // map of (suite, vector of cards in suite pile) pairs
    std::map<std::string, std::vector<Card *>> piles;
    // true when an invalid or non-play/discard cmd was entered by human player
    bool human_redo;

    void printCardsOnTable();
    void playCard(Player *p, Card *c);
    void discardCard(Player *p, Card *c);
    void getLegalPlays(std::vector<Card *> &legal_plays, Player *p);

    // visit returns d for print deck, r for ragequit, and 0 otherwise
    char visit(Human *human) override;
    char visit(DefaultComputer *comp) override;

    public:
        // returns true if game has ended
        bool endRound(Player *p1, Player *p2, Player *p3, Player *p4);
        explicit StandardGame(unsigned int turnNum); // ctor
};

#endif