cmake_minimum_required(VERSION 4.1)
project(DSA_2048_uniproject)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSA_2048_uniproject
        src/Main.cpp
        src/RandomPlayer.h
        src/BestFirstPlayer.h
        src/SmartPlayer.h
        src/MonteCarloPlayer.h
        src/bestplayer.h
        src/Board.h
        src/Game.h
        src/HumanPlayer.h
        src/Player.h
        src/Game.h)