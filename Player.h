#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Deck.h"
#include "Game.h"

class Player { // Element abstract base class
    unsigned int score; // accumulated score for the game
    // the cards the player is holding in the current round 
    std::vector<Card *> hand; // card * obtained using .get() on unique_ptrs
    std::vector<Card *> discarded;

    public:
        // makeMove returns d for print deck, r for ragequit, and 0 otherwise
        char virtual makeMove(Game &game) = 0; // accept(visitor)
        void printHand();
        void printDiscarded();
        int getSumDiscards();
        bool hasSpadeSeven(); // true if hand contains 7S
        bool handEmpty(); // true if hand.size() = 0
        Card *getCard(std::string name); // get card by name
        Card *getCard(int value, char suite); // get card by val and suite
        void addCard(Card *c); // adds card to hand
        void clearCards(); // clears hand and discarded vectors
        void removeCard(std::string name);
        void discardCard(std::string name);
        std::vector<Card *> getHand(); // why?
        int getScore(); // getter
        void setScore(unsigned int score); // setter

        explicit Player(unsigned int score); // ctor
        ~Player(); // dtor
};

#endif