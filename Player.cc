#include "Player.h"
using namespace std;

Player::Player(unsigned int score) : score{score} {} // ctor
Player::~Player() {} // dtor

bool Player::hasSpadeSeven() {
    for (auto &card : hand) {
        if (card->getName() == "7S") return true;
    }
    return false;
}

bool Player::handEmpty() { return hand.size() == 0; }
int Player::getScore() { return score; } // getter
int Player::setScore(unsigned int score) { this->score = score; } // setter