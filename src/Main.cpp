/*
 * Main.cpp
 *
 *  Created on: 12/01/2026
 *      Author: dongmo
 */

// Name: Amansingh Bhatia
// SID: 22207819
// I hereby certify that all code in this submission was completed
// by me and developed with the assistance of the AI tools listed
// below:
// NO AI tools were used to code
// I fully understand every part of my submission and am prepared to
// answer any questions related to it. No portion of this work was
// authored by another person. I have retained a backup copy of this
// assignment.


#include <ctime>
#include <iostream>

#include "bestplayer.h"
#include "MonteCarloPlayer.h"

using namespace std;

#include "Board.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "RandomPlayer.h"
#include "BestFirstPlayer.h"
#include "SmartPlayer.h"
 
int main() {
	srand(time(0));
	int boardSize = 4;
	cout << "Input the size of board (>= 3):" << endl;
	cin >> boardSize;
	if (boardSize < 3)
		boardSize = 3;
	else if (boardSize > 15)
		boardSize = 15;

	Board *board = new Board(boardSize);

	cout << "Empty cells: " << board->countEmptyCells() << endl;

	cout << "Choose a player to play: " << endl;
	cout << "1. Human Player" << endl;
	cout << "2. Random Player" << endl;
	cout << "3. Best First Player" << endl;
	cout << "4. Smart Player" << endl;
	cout << "5. Monte Carlo Player" << endl;
	cout << "6. Best Task 6 Player" << endl;

    //Add more option for different players 
	cout << "Others: Quit" << endl;

	int choice;
	cin >> choice;

	Player *p;

	if (choice == 1) {
		p = new HumanPlayer;
	}
	else if (choice == 2) {
		p = new RandomPlayer;
	}
	else if (choice == 3) {
		p = new BestFirstPlayer;
	}
	else if (choice == 4) {
		p = new SmartPlayer;
	}
	else if (choice == 5) {
		p = new MonteCarloPlayer;
	}
	else if (choice == 6) {
		p = new bestplayer;
	}


	else {
		return 0;
	}


	Game game(board, p);
	game.play();


	return 0;
}
