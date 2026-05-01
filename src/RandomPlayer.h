/*
 * HumanPlayer.h
 *
 *  Created on: 12/01/2026
 *      Author: dongmo
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

using namespace std;

#include "Board.h"
#include "Player.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <ctime>

class RandomPlayer: public Player {
public:
	RandomPlayer() {
		name = "Random Player";
	}
	char getMove(const Board&);
};



char RandomPlayer::getMove(const Board& board) {
	char move = '*';
	while (true) {
		int chosen = rand() % 4;
		if (chosen == 0) {
			move = 'l';
		}
		else if (chosen == 1) {
			move = 'r';
		}
		else if (chosen == 2) {
			move = 'u';
		}
		else if (chosen == 3) {
			move = 'd';
		}
		move = tolower(move);
		switch (move) {
		case 'l':
		case 'r':
		case 'u':
		case 'd':
			return move;
		case 'q':
			cout << "Thanks for playing! Final score: " << board.getScoreperStep()
					<< ".\n";
			return move;
		default:
			cout << "Invalid move! Use L/R/U/D or Q to quit.\n";
			continue;
		}
	}
	return move;
}

#endif /* RANDOMPLAYER_H_ */
