/*
 * Board.h
 *
 *  Created on: 12/01/2026
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

struct Tile {
	int x, y, value;
	Tile(int x=-1, int y=-1, int value=-1) :
		x(x), y(y), value(value) {}
};

class Board {
private:
	int boardSize;
	int **grid;
	int currentScore;
	int currentSteps;
	Tile newTile;
	int target = 2048;
	int bonus = 20000;

public:
	Board(int bs) {
		boardSize = bs;
		grid = new int *[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = 0;
			}

		currentScore = 0;
		currentSteps = 0;

		target = 2048 * ((int)((boardSize - 3) / 3) + 1);
		bonus = 10000 * ((int)(3 - (boardSize - 3) % 3));

		cout << "Based on the board size, the target number is " << target
			 << " and the bonus score if winning is " << bonus << ".\n"
			 << endl;

		addNewTile();
		addNewTile();
	}

	virtual ~Board() {
		for (int i = 0; i < boardSize; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board &cboard) {
		boardSize = cboard.getBoardSize();

		grid = new int *[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = cboard.getGrid(i, j);
			}
		currentScore = cboard.currentScore;
		currentSteps = cboard.currentSteps;
		target = cboard.target;
		bonus = cboard.bonus;
	}

	int getBoardSize() const { return boardSize; }
	int getGrid(int x, int y) const { return grid[x][y]; }
	int getTarget() const { return target; }
	int getBonus() const { return bonus; }
	int getCurrentSteps() const { return currentSteps; }
	int getCurrentScore() const { return currentScore; }
	double getScoreperStep() const {
		return currentSteps > 0 ? ((double)currentScore / (double)currentSteps)
								: 0;
	}
	bool checkchanged(const Board& board, const Board& newboard) {
		bool changed = false;
		for (int i=0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (board.getGrid(i, j) != newboard.getGrid(i, j)) {
					changed = true;
				}
			}
		}
		return changed;
	}
	Tile getNewTile() const { return newTile; }

	void addNewTile() {
		vector<int> empty;
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (grid[i][j] == 0) {
					empty.push_back(i * boardSize + j);
				}
			}
		}

		if (!empty.empty()) {
			int idx = rand() % empty.size();
			newTile.x = empty[idx] / boardSize;
			newTile.y = empty[idx] % boardSize;
			newTile.value =
				(rand() % 10 < 9) ? 2 : 4; // 90% chance of 2, 10% chance of 4
			grid[newTile.x][newTile.y] = newTile.value;
		}
	}

	bool hasWon() const {
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (grid[i][j] >= target)
					return true;
			}
		}
		return false;
	}

	void printBoard() const {
		cout << "     ";
		for (int j = 0; j < boardSize; j++) {
			cout << j + 1 << "     ";
		}
		cout << endl;

		cout << "   ";
		for (int j = 0; j < boardSize; j++) {
			cout << "------";
		}
		cout << endl;

		for (int i = 0; i < boardSize; i++) {
			cout << setw(2) << i + 1 << " ";

			for (int j = 0; j < boardSize; j++) {
				if (grid[i][j] == 0) {
					if (j == 0) {
						cout << "|     |";
					} else {
						cout << "     |";
					}
				} else {
					if (j == 0) {
						cout << "|" << setw(5) << grid[i][j] << "|";
					} else {
						cout << setw(5) << grid[i][j] << "|";
						;
					}
				}
			}
			cout << endl;

			cout << "   ";
			for (int j = 0; j < boardSize; j++) {
				cout << "------";
			}
			cout << endl;
		}
		cout << "Current score: " << currentScore
			 << " Total steps: " << currentSteps << "." << endl;
		cout << "Current score per step: " << getScoreperStep() << "." << endl;
	}


	
	void makeMove(char direction);
	vector<int> merge(list<int> row);
	int countEmptyCells() const;
	bool canMove() const;
	int getMax() {
		int max=0;
		for (int i = 0; i < getBoardSize(); i++) {
			for (int j = 0; j < getBoardSize() ; j++) {

				if (getGrid(i, j) > max) {
					max = getGrid(i, j);
				}
			}
		}
		return max;
	}
};

int Board::countEmptyCells() const {


	int number = 0; 
	for (int i = 0; i < boardSize; i++){
		
		for (int j=0; j < boardSize; j++){
			if (grid[i][j] == 0){
				number++; 
			}
		}
	}

	return number;
}


bool Board::canMove() const {

	if (countEmptyCells() != 0) {
		return true;
	}
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (i+1 < boardSize && grid[i][j] == grid[i+1][j]) {
				return true;
			}
			if (j+1 < boardSize && grid[i][j] == grid[i][j+1]) {
				return true;
			}
		}
	}


	return false;
}

vector<int> Board::merge(list<int> row) {
	vector<int> mergedRow;


	list<int>::iterator it = row.begin();
	while (it != row.end()) {
		if (next(it) != row.end()) {
			if (*it == *next(it)) {
				mergedRow.push_back(*it + *next(it));
				currentScore += (*it + *next(it));
				advance(it, 2);
			}
			else {
				mergedRow.push_back(*it);
				advance(it, 1);
			}
		}
		else {
			mergedRow.push_back(*it);
			advance(it, 1);
		}
	}
	while (mergedRow.size() < boardSize) {
		mergedRow.push_back(0);

	}



	return mergedRow;
}

void Board::makeMove(char direction) {

	for (int i = 0; i < boardSize; i++) {
		list<int> row;
		for (int j = 0; j < boardSize; j++) {
			if ((direction == 'l' || direction == 'r') && grid[i][j] != 0)
				row.push_back(grid[i][j]);

			if ((direction == 'u' || direction == 'd') && grid[j][i] != 0) {
				row.push_back(grid[j][i]);
			}

		}

		if (direction == 'r' || direction == 'd')
			row.reverse();

		if (!row.empty()) {
			vector<int> merged = merge(row);
			if (direction == 'r' || direction == 'd')
				reverse(merged.begin(), merged.end());
			for (int j = 0; j < boardSize; j++) {
				if (direction == 'l' || direction == 'r')
					grid[i][j] = merged[j];
				if (direction == 'u' || direction == 'd')
					grid[j][i] = merged[j];


			}
		}
	}

	currentSteps++;

}



#endif /* BOARD_H_ */