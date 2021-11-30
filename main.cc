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


    deck.printDeck();


    // // Create vector of players
    // vector<unique_ptr<Player>> players;
    // for (int i = 1; i < 5; ++i) {
    //     cout << "Is Player" << i << "a human (h) or a computer (c)?" << endl;
    //     char playerType;
    //     cin >> playerType;
    //     if (playerType == 'h') players.push_back(make_unique<Human>(0));
    //     if (playerType == 'c') players.push_back(make_unique<DefaultComputer>(0));
    // }

    // // Start the game
    // while (1) {
    //     deck.shuffle();
    //     deck.dealCards(
    //         players.at(0).get(), // Player1
    //         players.at(1).get(), // Player2
    //         players.at(2).get(), // Player3
    //         players.at(3).get()  // Player4
    //     );
    //     // determine starting player and initilize a StandardGame round
    //     unsigned int startingPlayer;
    //     for (int i = 0; i < 4; ++i) {
    //         if (players.at(i)->hasSpadeSeven()) {
    //             startingPlayer = i;
    //             break;
    //         }
    //     }
    //     cout << "A new round begins. It's Player";
    //     cout << startingPlayer << "'s turn to play" << endl;//could move this to StandardGame ctor, but then would have to turn off the ctor skipping stuff with a flag in makefile
    //     StandardGame game_round{startingPlayer};
    //     // The round continues until everybody has an empty hand
    //     while(!(players.at(0)->handEmpty() && players.at(1)->handEmpty() && 
    //             players.at(2)->handEmpty() && players.at(3)->handEmpty())) {
    //         // While player hasn't discarded or played a card its still their turn
    //         int turnNum = game_round.getTurnNum();
    //         char moveResult = players.at(turnNum).get()->makeMove(game_round);
    //         while(moveResult != '0') {
    //             if (moveResult == 'd') { // print deck
    //                 deck.printDeck();
    //             } else { // ragequit
    //                 cout << "Player" << turnNum + 1 << "ragequits.";
    //                 cout << " A computer will now take over." << endl; // Move this to the visit(Human) method in StandardGame since it pretains to using CLI interface
    //                 // replace human player with computer
    //                 auto old_player = move(players.at(turnNum));
    //                 players.at(turnNum) = make_unique<DefaultComputer>(old_player->getScore());
    //                 // copy human players hand
    //                 for (auto card : old_player->hand) {
    //                     players.at(turnNum)->hand.push_back(card);
    //                 }
    //             }
    //         }
    //     }
    //     bool game_ended = game_round.endRound(
    //         players.at(0).get(), // Player1
    //         players.at(1).get(), // Player2
    //         players.at(2).get(), // Player3
    //         players.at(3).get()  // Player4
    //     );
    //     if (game_ended) break;
    // }
}