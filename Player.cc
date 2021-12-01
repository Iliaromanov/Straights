#include "Player.h"
#include <iostream>
#include <algorithm>
using namespace std;

Player::Player(unsigned int score) : score{score} {} // ctor
Player::~Player() {} // dtor

Card *Player::getCard(std::string name) { /// <-----check if returning Card * causes mem leak, shouldn't cus card is freed by unique_ptr, but if it does, thats gay
    // return find_if(hand.begin(), hand.end(),
    //     [name](Card *c) { return c->getName() == name; }
    // );
    for (auto card : hand) {
        if (card->getName() == name) return card;
    }
    return nullptr;
}

bool Player::hasSpadeSeven() {
    return getCard("7S") != nullptr;
}

void Player::removeCard(string name) {
    hand.erase(
        remove_if(hand.begin(), hand.end(),
            [name](Card *c) {return c->getName() == name;}
        ),
        hand.end()   
    );
}

void Player::discardCard(string name) {
    for (auto card : hand) {
        if (card->getName() == name) {
            removeCard(card->getName());
            discarded.push_back(card);
            return;
        }
    }
}

void Player::printHand() {
    for (auto card : hand) cout << " " << card->getName();
    cout << endl;
}
void Player::printDiscarded() {
    for (auto card : hand) cout << " " << card->getName();
    cout << endl;
}

int Player::getSumDiscards() {
    int sum = 0;
    for (auto card : discarded) sum += card->getVal();
    return sum;
}

bool Player::handEmpty() { return hand.size() == 0; }
int Player::getScore() { return score; } // getter
void Player::setScore(unsigned int score) { this->score = score; } // setter

/* Methods could add to make hand and discarded private 
(allowing both Deck and Game to do what they need without actaully having access to hand and discarded)

// does hand.clear(); discarded.clear(); would be used when clearing in Deck::dealCards
clearCards()

// adds card to hand; would be used in Deck::dealCards
addCard(Card *card)

// Just removes card from hand; this would be used when card is played to a pile
removeCard(string name)

// Moves card from hand to discarded
discardCard(string name)

// would be used in StandardGame when checking if a card is in players hand
// eg. if (p->getCard("5H") != p->getHandEnd()) // "5H" is in players hand
getHandEnd() { return hand.end(); }

*/