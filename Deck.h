#ifndef DECK_H
#define DECK_H
#include <string>
#include <memory>
#include <vector>
#include <random>

class Player;

class Deck {
    class Card {
        int value; // 1 to 13
        char suite; // H, D, C, or S
        std::string name; // eg. AS or 7H or KD etc.

        public: 
            Card(int value, char suite, std::string name); // ctor
            ~Card();
            std::string getName(); // getter
    };

    std::vector<std::unique_ptr<Card>> cards; // 52 cards
    std::default_random_engine rng; // for shuffling

    public:
        void shuffle(); // shuffles cards in deck using rng
        void dealCards(Player *p1, Player *p2, Player *p3, Player *p4); // populates players hand vec
        void printDeck(); // prints cards in the cards vector
        Deck(std::default_random_engine rng); // ctor
        ~Deck(); // dtor
};


#endif