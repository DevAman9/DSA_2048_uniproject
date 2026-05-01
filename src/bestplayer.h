//
// Created by Aman Bhatia on 14/4/2026.
//

#ifndef TASK2_2_BESTPLAYER_H
#define TASK2_2_BESTPLAYER_H

using namespace std;

#include "Board.h"
#include "Player.h"
#include <vector>
#include <queue>



class bestplayer: public Player {
    double heuristic(const Board& board) {
        double score = 0;
        double max = 0;

        for (int i = 0; i < board.getBoardSize(); i++) {
            for (int j = 0; j < board.getBoardSize() ; j++) {
                if (i < board.getBoardSize() - 1) {
                    if (board.getGrid(i, j) == board.getGrid(i+1, j)) {
                        score = score + board.getGrid(i, j);
                    }
                    if (board.getGrid(i, j) >= board.getGrid(i+1, j)) {
                        score = score + board.getGrid(i, j);
                    }
                }
                if (j < board.getBoardSize() - 1) {
                    if (board.getGrid(i, j) == board.getGrid(i, j+1) ) {
                        score = score + board.getGrid(i, j);
                    }
                    if (board.getGrid(i, j) >= board.getGrid(i, j+1)) {
                        score = score + board.getGrid(i, j);
                    }
                }

                if (board.getGrid(i, j) > max) {
                    max = board.getGrid(i, j);
                }
            }
        }



        if (board.getGrid(0, 0) == max || board.getGrid(board.getBoardSize()-1, board.getBoardSize()-1) == max || board.getGrid(0, board.getBoardSize()-1) == max || board.getGrid(board.getBoardSize()-1, 0) == max) {
            if (max == 2048) {
                max *= 5000;
            }
            if (max == 1024) {
                max *= 40;
            }
            else {
                max *= 60;
            };
        }
        else {
            max *= 40;
        }



        score = score + (board.countEmptyCells() * 500) + max;
        return score;
    }


    double lookahead(Board & tempboard, int depth) {
        if (depth == 0 || !tempboard.canMove()) {
            return heuristic(tempboard);
        }
        vector<char> moves = {'l', 'r', 'u', 'd'};
        double best = -1;
        for (int i = 0; i < 4; i ++) {
            Board sim_board(tempboard);

            sim_board.makeMove(moves[i]);
            if (sim_board.checkchanged(tempboard, sim_board)) {
                sim_board.addNewTile();
                double score_val = lookahead(sim_board, depth -1);
                if (score_val > best) {
                    best = score_val;
                }
            }

        }
        return best;

    }
public:
    bestplayer() {
        name = "Best Player";
    }
    char getMove(const Board&);
};

char bestplayer::getMove(const Board & board) {
    if (!board.canMove()) {
        return 'q';
    }
    vector<char> moves = {'l', 'r', 'u', 'd'};
    priority_queue<Move> dir;

    for (int i = 0; i < 4; i ++) {
        Board tempboard(board);
        char direction = moves[i];
        tempboard.makeMove(direction);
        if (tempboard.checkchanged(board, tempboard)) {
            tempboard.addNewTile();
            double score = lookahead(tempboard, 5);
            cout << "  Score: " << score << " | Direction: " << direction << endl ;
            Move m(direction, score);
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


#endif //TASK2_2_BESTPLAYER_H