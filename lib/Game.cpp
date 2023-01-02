#include "Game.hpp"
#include <iostream>


Game::Game(std::string mapPath, int tPS, int ticksPlayer, int ticksGhosts, PacmanAgent* _pacmanAgent) :
        pacmanAgent(_pacmanAgent),
        board(new Board(mapPath)),
        ticksPerSecond(tPS)

{
    ticksPerMovePlayer = ticksPlayer;
    ticksPerMoveGhosts = ticksGhosts;
}

Game::~Game() {
    //delete[] board;
    delete[] pacmanAgent;
}

void Game::printBoard() {
    board->printBoard();
}

bool Game::update() {
    pacmanAgent->updateState(board);
    board->updateGhosts();
    board->increaseGameTick();
    return !board->isGameOver();
}
