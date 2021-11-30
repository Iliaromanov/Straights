#include "Deck.h"
#include <iostream>
using namespace std;

// Card ctor
Deck::Card::Card(int value, char suite, string name) : value{value}, suite{suite}, name{name} {}

Deck::Card::~Card() {}

string Deck::Card::getName() { return name; }

// Deck ctor
Deck::Deck(default_random_engine rng) : rng{rng} {
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    vector<char> suites = {'H', 'D', 'C', 'S'};
    vector<string> nameChars = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
    };

    for (auto suite : suites) {
        for (int i = 0; i < 13; ++i) {
            cards.push_back(move(make_unique<Card>(
                values.at(i), suite, nameChars.at(i) + suite
            )));
        }
    }
}

// Deck dtor
Deck::~Deck() {}

// shuffles cards in deck using rng
void Deck::shuffle() {

}

// deals 13 cards to each player
void Deck::dealCards(Player *p1, Player *p2, Player *p3, Player *p4) {

}

// prints cards in the cards vector in 4 rows of 13
void Deck::printDeck() {
    int count = 0;
    for (auto const &card : cards) {
        cout << card->getName() << " ";
        if (++count == 13) {
            cout << endl;
            count = 0;
        }
    }
}