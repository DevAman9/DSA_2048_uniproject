//
// Created by Aman Bhatia on 31/3/2026.
//

#ifndef TASK2_2_BESTFIRSTPLAYER_H
#define TASK2_2_BESTFIRSTPLAYER_H

using namespace std;

#include "Board.h"
#include "Player.h"
#include <vector>
#include <queue>

class BestFirstPlayer: public Player {
    double heuristic(const Board& board) {
        double score = 0;

        for (int i = 0; i < board.getBoardSize(); i++) {
            for (int j = 0; j < board.getBoardSize() - 1; j++) {
                if (board.getGrid(i, j) >= board.getGrid(i, j+1)) {
                    score = score + board.getGrid(i, j);
                }
            }
        }

        for (int i = 0; i < board.getBoardSize() - 1; i++) {
            for (int j = 0; j < board.getBoardSize(); j++) {
                if (board.getGrid(i, j) >= board.getGrid(i+1, j)) {
                    score = score + board.getGrid(i, j);
                }
            }
        }

        score += board.countEmptyCells() * 20;

        return score;
    }

public:
    BestFirstPlayer() {
        name = "Best Player";
    }
    char getMove(const Board&);
};

char BestFirstPlayer::getMove(const Board &board) {
    if (!board.canMove()) {
        return 'q';
    }

    priority_queue<Move> dir;

    vector<char> moves = {'l', 'r', 'u', 'd'};

    for (int i = 0; i < 4; i++) {
        Board tempboard(board);
        char direction = moves[i];
        tempboard.makeMove(direction);
        if (tempboard.checkchanged(board, tempboard)) {
            Move m(direction, heuristic(tempboard));
            dir.push(m);
        }
    }

    if (!dir.empty()) {
        return dir.top().direction;

    }
    else {
        return 'q';
    }

}







#endif //TASK2_2_BESTFIRSTPLAYER_H