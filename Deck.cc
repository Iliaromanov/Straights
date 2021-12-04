#include "Deck.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Card ctor
Card::Card(int value, char suite, string name) : value{value}, suite{suite}, name{name} {}

// Card dtor
Card::~Card() {}

// Card class gettors
int Card::getVal() { return value; }
char Card::getSuite() { return suite; }
string Card::getName() { return name; }


// Deck ctor
Deck::Deck(default_random_engine rng) : rng{rng} {
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    vector<char> suites = {'H', 'D', 'C', 'S'};
    vector<string> nameChars = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"
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
    std::shuffle(cards.begin(), cards.end(), rng);
}

// deals 13 cards to each player
void Deck::dealCards(Player *p1, Player *p2, Player *p3, Player *p4) {
    // clear hand and discarded vectors from prev round
    p1->clearCards();
    p2->clearCards();
    p3->clearCards();
    p4->clearCards();
    // deal cards, 13 per player
    for (int i = 0; i < 13; ++i) p1->addCard(cards.at(i).get());
    for (int i = 13; i < 26; ++i) p2->addCard(cards.at(i).get());
    for (int i = 26; i < 39; ++i) p3->addCard(cards.at(i).get());
    for (int i = 39; i < 52; ++i) p4->addCard(cards.at(i).get());
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