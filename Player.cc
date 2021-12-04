#include "Player.h"
#include <iostream>
#include <algorithm>
using namespace std;

Player::Player(unsigned int score) : score{score} {} // ctor
Player::~Player() {} // dtor

Card *Player::getCard(std::string name) {
    for (auto card : hand) {
        if (card->getName() == name) return card;
    }
    return nullptr;
}

Card *Player::getCard(int value, char suite) {
    for (auto card : hand) {
        if (card->getVal() == value && card->getSuite() == suite) return card;
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
    for (auto card : discarded) cout << " " << card->getName();
    cout << endl;
}

int Player::getSumDiscards() {
    int sum = 0;
    for (auto card : discarded) sum += card->getVal();
    return sum;
}

void Player::addCard(Card *card) { 
    hand.push_back(card);
    sort(hand.begin(), hand.end(),
        [](Card *c1, Card *c2) {
            return (c1->getVal() < c2->getVal()) || 
                   (c1->getVal() == c2->getVal() && c1->getSuite() < c2->getSuite());
        }
    );
}
void Player::clearCards() {
    hand.clear();
    discarded.clear();
}
bool Player::handEmpty() { return hand.size() == 0; }
vector<Card *> Player::getHand() { return hand; } // very ugly getter
int Player::getScore() { return score; } // getter
void Player::setScore(unsigned int score) { this->score = score; } // setter
