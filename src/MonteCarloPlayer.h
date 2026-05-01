//
// Created by Aman Bhatia on 04/4/2026.
//

#ifndef TASK2_2_MONTECARLOPLAYER_H
#define TASK2_2_MONTECARLOPLAYER_H

using namespace std;



#include "Board.h"
#include "Player.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <ctime>


mt19937 rng(random_device{}());
uniform_int_distribution<int> dist(0, 3);

class MonteCarloPlayer: public Player {
    double heuristic(const Board& board) {
        double score = 0;
        double max = 0;

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

        for (int i = 0; i < board.getBoardSize(); i++) {
            for (int j = 0; j < board.getBoardSize() ; j++) {
                if (board.getGrid(i, j) > max) {
                    max = board.getGrid(i, j);
                }
            }
        }



        score += board.countEmptyCells() * 200 + ( max * 20);

        return score;
    }

    double simulate(const Board& tempboard) {
        double total_score = 0;
        for (int i = 0; i < 50 ; i++) {
            Board simulation(tempboard );
            total_score += expansion(simulation, 30);
        }
        return total_score ;

    }

    double expansion(Board simulation, int depth) {
        int steps = 0;
        vector<char> moves = {'l', 'r', 'u', 'd'};
        while (steps < depth && simulation.canMove()) {
            int i = dist(rng);

            Board new_sim(simulation);

            new_sim.makeMove(moves[i]);

            if (new_sim.checkchanged(simulation, new_sim)) {
                simulation.makeMove(moves[i]);
                simulation.addNewTile();
                steps++;
            }

        }

        return heuristic(simulation);
    }

public:
    MonteCarloPlayer() {
        name = "Monte Carlo Player";
    }
    char getMove(const Board&);
};

char MonteCarloPlayer::getMove(const Board& board) {
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
            int avg_score = simulate(tempboard);
            cout << "  Score: " << avg_score << " | Direction: " << direction << endl ;
            Move m(direction, avg_score);
            dir.push(m);
        }

    }
    if (!dir.empty()) {
        return dir.top().direction;
    }

    return 'q';

};

#endif //TASK2_2_MONTECARLOPLAYER_H