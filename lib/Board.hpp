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
    PieceBoard* pieceBoard;
    Entity* player;
    Position pacmanStartingPos;
    Ghost* ghosts[4];
    Position ghostsStartingPos[4];
    int points;
    int foodCount;
    int currentGameTick;
    bool gameOver;
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
    void moveCurveTunnel(Entity* ghost);
    void setCurveDirection(Entity* ghost);
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
};

#endif //PACTEAM2_BOARD_HPP
