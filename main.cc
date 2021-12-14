#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include "DefaultComputer.h"
#include "Human.h"
#include "StandardGame.h"
using namespace std;


int main( int argc, char * argv[] ) {
	// Get seed
	unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
	if ( argc > 1 ) {
		try {
			seed = stoi( string{ argv[1] } );
		} catch( invalid_argument & e ) {
			cerr << e.what() << endl;
			return 1;
		} catch( out_of_range & e ) {
			cerr << e.what() << endl;
			return -1;
		}
	}
	default_random_engine rng{seed};

    // Create deck of cards
    Deck deck{rng};

    // Create vector of players
    vector<unique_ptr<Player>> players;
    for (int i = 1; i < 5; ++i) {
        cout << "Is Player" << i << " a human (h) or a computer (c)?" << endl;
        char player_type;
        cin >> player_type;
        if (player_type == 'h') players.push_back(make_unique<Human>(0));
        if (player_type == 'c') players.push_back(make_unique<DefaultComputer>(0));
    }


    // Start the game
    while (1) {
        deck.shuffle();
        deck.dealCards(
            players.at(0).get(), // Player1
            players.at(1).get(), // Player2
            players.at(2).get(), // Player3
            players.at(3).get()  // Player4
        );
        // determine starting player and initilize a StandardGame round
        unsigned int startingPlayer;
        for (int i = 0; i < 4; ++i) {
            if (players.at(i)->hasSpadeSeven()) {
                startingPlayer = i;
                break;
            }
        }
        StandardGame game_round{startingPlayer};
        // The round continues until everybody has an empty hand
        while(!(players.at(0)->handEmpty() && players.at(1)->handEmpty() && 
                players.at(2)->handEmpty() && players.at(3)->handEmpty())) {
            // While player hasn't discarded or played a card its still their turn
            int turn_num = game_round.getTurnNum();
            char move_result = players.at(turn_num).get()->makeMove(game_round);
            while(move_result == 'd') { // human calls deck command
                deck.printDeck();
                move_result = players.at(turn_num).get()->makeMove(game_round);
            }
            if (move_result == 'q') { // human calls ragequit command
                // replace human player with computer
                auto old_player = move(players.at(turn_num));
                players[turn_num] = make_unique<DefaultComputer>(old_player->getScore());
                // copy human players hand
                for (auto card : old_player->getHand()) {
                    players[turn_num]->addCard(card);
                }
                // copy human players discarded
                for (auto card : old_player->getDiscarded()) {
                    players[turn_num]->addCard(card);
                    players[turn_num]->discardCard(card->getName());
                }
                // let the computer player make a play
                players.at(turn_num).get()->makeMove(game_round);
            }
            game_round.nextTurn();
        }
        bool game_ended = game_round.endRound(
            players.at(0).get(), // Player1
            players.at(1).get(), // Player2
            players.at(2).get(), // Player3
            players.at(3).get()  // Player4
        );
        if (game_ended) break;
    }
}