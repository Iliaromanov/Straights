#include "StandardGame.h"
#include "DefaultComputer.h"
#include "Human.h"
#include "Deck.h"
#include <algorithm>
#include <iostream>
using namespace std;


StandardGame::StandardGame(unsigned int turnNum) : Game{turnNum}, human_redo{false} { // ctor
    cout << "A new round begins. It's Player";
    cout << turnNum+1 << "'s turn to play" << endl;

    // Initialize the pile for each suite to an empty vector
    piles["Clubs:"].clear();
    piles["Diamonds:"].clear();
    piles["Hearts:"].clear();
    piles["Spades:"].clear();
}

void StandardGame::printCardsOnTable() {
    cout << "Cards on the table:" << endl;
    for (auto &pile : piles) {
        cout << pile.first;
        for (auto &card : pile.second) {
            if (card->getVal() == 10) {
                cout << " 10";
            } else {
                cout << " " <<  card->getName()[0];
            }
        }
        cout << endl;
    }
}

// prints players hand
void printHand(Player *p) {
    cout << "Your hand:";
    p->printHand();
}

void StandardGame::playCard(Player *player, Card *card) {
    cout << "Player" << getTurnNum()+1 << " plays ";
    cout << card->getName() << "."<< endl;

    // Place the card into its corresponding pile
    if (card->getSuite() == 'C') {
        // if its a 7 or the largest card just push it to the end pile
        if (card->getVal() == 7 || card->getVal() > piles["Clubs:"].back()->getVal()) {
            piles["Clubs:"].push_back(card);
        // otherwise insert it to the start of the pile
        } else {
            piles["Clubs:"].insert(piles["Clubs:"].begin(), card);
        }
    } else if (card->getSuite() == 'D') {
        if (card->getVal() == 7 || card->getVal() > piles["Diamonds:"].back()->getVal()) {
            piles["Diamonds:"].push_back(card);
        } else {
            piles["Diamonds:"].insert(piles["Diamonds:"].begin(), card);
        }
    } else if (card->getSuite() == 'H') {
        if (card->getVal() == 7 || card->getVal() > piles["Hearts:"].back()->getVal()) {
            piles["Hearts:"].push_back(card);
        } else {
            piles["Hearts:"].insert(piles["Hearts:"].begin(), card);
        }
    } else {
        if (card->getVal() == 7 || card->getVal() > piles["Spades:"].back()->getVal()) {
            piles["Spades:"].push_back(card);
        } else {
            piles["Spades:"].insert(piles["Spades:"].begin(), card);
        }
    }
    
    // Remove card from players hand
    player->removeCard(card->getName());
}

void StandardGame::discardCard(Player *player, Card *card) {
    cout << "Player" << getTurnNum()+1 << " discards ";
    cout << card->getName() << "." << endl;
    player->discardCard(card->getName());
}

void StandardGame::getLegalPlays(vector<Card *> &legal_plays, Player *player) {
    // If all piles are empty, then the only legal play must be 7S and the player must have it
    if (find_if(piles.begin(), piles.end(), 
        [](pair<string, vector<Card *>> p) { return p.second.size() > 0; }) == piles.end()
    ) {
        legal_plays.push_back(player->getCard("7S"));
        if (!human_redo) cout << "Legal plays: 7S" << endl;
        return;
    }

    // Get edge cards of each suite pile and check if player has cards of +-1 value
    for (auto pile : piles) {
        if (pile.second.size()) { 
            // check front of pile
            Card *card = pile.second.at(0);
            Card *legal_play = player->getCard(card->getVal()-1, card->getSuite());
            if (legal_play) legal_plays.push_back(legal_play);

            // check back of pile
            card = pile.second.back();
            legal_play = player->getCard(card->getVal()+1, card->getSuite());
            if (legal_play) legal_plays.push_back(legal_play);
        }
    }

    // Add 7s to legal plays if they are in players hand
    if (player->getCard("7C")) legal_plays.push_back(player->getCard("7C"));
    if (player->getCard("7D")) legal_plays.push_back(player->getCard("7D"));
    if (player->getCard("7H")) legal_plays.push_back(player->getCard("7H"));
    // sort so DefaultComputer player picks correctly
    sort(legal_plays.begin(), legal_plays.end(), 
        [](Card *c1, Card *c2) {
            return c1->getVal() < c2->getVal() || 
                   c1->getVal() == c2->getVal() && c1->getSuite() < c2->getSuite();
        }
    );

    if (!human_redo) { 
        cout << "Legal plays:";
        for (auto card : legal_plays) cout << " " << card->getName();
        cout << endl;
    }
}

// visit returns d for print deck, r for ragequit, and 0 otherwise
char StandardGame::visit(DefaultComputer *comp) {
    if (!human_redo) {
        cout << "---------------------------------------------------" << endl;
        cout << "It's Player" << getTurnNum()+1 << "'s turn to play." << endl;
        printCardsOnTable();
        // print players hand
        printHand(comp);
    }

    // Get legal plays
    vector<Card *> legal_plays;                     /// <------------------check if this causes mem leak, shouldn't cus card is freed by unique_ptr, but if it does, thats gay
    getLegalPlays(legal_plays, comp);

    human_redo = false;

    // Discard first card in hand if no legal plays available
    if (!legal_plays.size()) {
        discardCard(comp, comp->getHand().at(0));
    } else { // make the first legal_play
        playCard(comp, legal_plays.at(0));
    }
    return '0';
}

// visit returns d for print deck, r for ragequit, and 0 otherwise
char StandardGame::visit(Human *human) {
    if (!human_redo) {
        cout << "---------------------------------------------------" << endl;
        cout << "It's Player" << getTurnNum()+1 << "'s turn to play." << endl;
        printCardsOnTable();
        // print players hand
        printHand(human);
    }

    // Get legal plays
    vector<Card *> legal_plays;                     /// <------------------check if this causes mem leak, shouldn't cus card is freed by unique_ptr, but if it does, thats gay
    getLegalPlays(legal_plays, human);

    // Read command from stdin
    while (1) {
        cout << "> ";
        string cmd;
        cin >> cmd;
        if (cmd == "quit") exit(0);
        if (cmd == "deck") {
            human_redo = true;
            return 'd';
        }
        if (cmd == "ragequit") {
            cout << "Player" << getTurnNum()+1 << " ragequits.";
            cout << " A computer will now take over." << endl;
            human_redo = true;
            return 'q';
        }
        if (cmd == "play") {
            string card_name;
            cin >> card_name;
            // check if the card is in players hand
            if (!human->getCard(card_name)) {
                cout << "you don't have this card in your hand." << endl;
                continue;
            }
            // Check for legal play
            if (find_if(legal_plays.begin(), legal_plays.end(),
                [card_name](Card *c) {return c->getName() == card_name;})
                == legal_plays.end()) {
                cout << "This is not a legal play." << endl;
                continue;
            } else {
                playCard(human, human->getCard(card_name));
                human_redo = false;
                return '0';
            }
        } else if (cmd == "discard") {
            string card_name;
            cin >> card_name;
            if (!human->getCard(card_name)) {
                cout << "you don't have this card in your hand." << endl;
                continue;
            }
            if (legal_plays.size()) {
                cout << "You have a legal play. ";
                cout << "You may not discard." << endl;
                continue;
            } else {
                discardCard(human, human->getCard(card_name));
                human_redo = false;
                return '0';
            }
        } else {
            cout << "invalid command. try again." << endl;
        }
    }
}

// returns true if game has ended
bool StandardGame::endRound(Player *p1, Player *p2, Player *p3, Player *p4) {
    cout << "Player1's discards:";
    p1->printDiscarded();
    cout << "Player1's score: " << p1->getScore();
    cout << " + " << p1->getSumDiscards() << " = ";
    p1->setScore(p1->getScore() + p1->getSumDiscards());
    cout << p1->getScore() << endl;

    cout << "Player2's discards:";
    p2->printDiscarded();
    cout << "Player2's score: " << p2->getScore();
    cout << " + " << p2->getSumDiscards() << " = ";
    p2->setScore(p2->getScore() + p2->getSumDiscards());
    cout << p2->getScore() << endl;

    cout << "Player3's discards:";
    p3->printDiscarded();
    cout << "Player3's score: " << p3->getScore();
    cout << " + " << p3->getSumDiscards() << " = ";
    p3->setScore(p3->getScore() + p3->getSumDiscards());
    cout << p3->getScore() << endl;

    cout << "Player4's discards:";
    p4->printDiscarded();
    cout << "Player4's score: " << p4->getScore();
    cout << " + " << p4->getSumDiscards() << " = ";
    p4->setScore(p4->getScore() + p4->getSumDiscards());
    cout << p4->getScore() << endl;

    // Check for end of game
    bool game_won = false;
    if (p1->getScore() >= 80 || p2->getScore() >= 80 ||
        p3->getScore() >= 80 || p4->getScore() >= 80) {
        game_won = true;
        int min_score = p1->getScore();

        if (p2->getScore() < min_score) min_score = p2->getScore();
        if (p3->getScore() < min_score) min_score = p3->getScore();
        if (p4->getScore() < min_score) min_score = p4->getScore();

        if (p1->getScore() == min_score) cout << "Player1 wins!" << endl;
        if (p2->getScore() == min_score) cout << "Player2 wins!" << endl;
        if (p3->getScore() == min_score) cout << "Player3 wins!" << endl;
        if (p4->getScore() == min_score) cout << "Player4 wins!" << endl;
    }
    return game_won;
}
