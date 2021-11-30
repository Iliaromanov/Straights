#ifndef STDGAME_H
#define STDGAME_H
#include "Game.h"
#include <memory>
#include <vector>

class Player;
class Card;

class StandardGame : public Game {
    std::vector<std::vector<Card *>> piles;
    void visit(Human *human) override;
    void visit(DefaultComputer *comp) override;

    public:
        // returns true if game has ended
        bool endRound(Player *p1, Player *p2, Player *p3, Player *p4);
        // VVV DO THE BELOW STUFF IN THIS METHOD VVV

        // print the score and discards for the round and clear players discards vecs

        // // Check if anybody reached 80
        // bool game_won = false;
        // for (int i = 0; i < 4; ++i) {
        //     if (players.at(i)->getScore() >= 80) {
        //         cout << "Player" << i + 1 << " wins!" << endl;
        //         game_won = true;
        //     }
        // }
        // if (game_won) break;
        
        explicit StandardGame(unsigned int turnNum); // : Game{turnNum} {}
};

#endif