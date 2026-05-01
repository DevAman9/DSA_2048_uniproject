//
// Created by Aman Bhatia on 31/3/2026.
//

#ifndef TASK2_2_SMARTPLAYER_H
#define TASK2_2_SMARTPLAYER_H

using namespace std;

#include "Board.h"
#include "Player.h"
#include <vector>
#include <queue>

class SmartPlayer: public Player {
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

        score += board.countEmptyCells() * 10;

        return score;
    }

public:
    SmartPlayer() {
        name = "Smart Player";
    }
    char getMove(const Board&);
};

char SmartPlayer::getMove(const Board &board) {
    if (!board.canMove()) {
        return 'q';
    }

    priority_queue<Move> dir;

    vector<char> moves = {'l', 'r', 'u', 'd'};

    for (int i = 0; i < 4; i++) {
        priority_queue<Move> inner_dir;
        Board tempboard(board);
        char direction = moves[i];
        tempboard.makeMove(direction);
        for (int j = 0; j < 4; j++) {
            Board inner_board(tempboard);
            char inner_direction = moves[j];
            inner_board.makeMove(inner_direction);
            if (inner_board.checkchanged(tempboard, inner_board)) {
                Move m(direction, heuristic(inner_board));
                inner_dir.push(m);
            }

        }
        if (tempboard.checkchanged(board, tempboard) && !inner_dir.empty()) {
            Move m(direction, inner_dir.top().value);
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


#endif //TASK2_2_SMARTPLAYER_H