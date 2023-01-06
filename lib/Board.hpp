#ifndef PACTEAM2_BOARD_HPP
#define PACTEAM2_BOARD_HPP
#pragma once

#include <vector>
#include <string>
#include "Entity.hpp"
#include "ghosts/Ghost.hpp"
#include "PieceBoard.hpp"

class Board {
private:
    int width;
    int height;
    //pieceBoard stores all the pieces inside our board
    PieceBoard* pieceBoard;
    //pacman entity
    Entity* player;
    //initial position of pacman
    Position pacmanStartingPos;
    //array with the 4 ghosts
    Ghost* ghosts[4];
    //initial positions of the ghosts
    Position ghostsStartingPos[4];
    int points;
    //we havefoodCount variable to know when pacman has eaten all the foods.
    int foodCount;
    int currentGameTick;
    bool gameOver;
    int pacmanDeaths;
public:
    Board(const Board& board);
    Board(std::string mapPath);
    ~Board();
    void printBoard();
    void movePlayer();
    void moveGhost(int ghostId);
    void changePlayerDirection(Direction newDirection);
    void changeGhostDirection(int ghostId, Direction newDirection);
    void updateGhosts();
    void setCurveDirection(Ghost* ghost);
    Board* clone();
    std::vector<Board*> getPacmanChildStates();
    std::vector<Board*> getGhostsChildStates();
    Entity* getPacman();
    PieceBoard* getPieceBoard();
    int getWidth();
    int getHeight();
    int getPoints();
    Ghost* collisionGhosts(Position pos);
    void ghostEatPacman();
    void pacmanEatGhost(Ghost* g);
    bool isGameOver();
    void increaseGameTick();
    int getGameTick();
};

#endif //PACTEAM2_BOARD_HPP
