#ifndef PACTEAM2_GAME_HPP
#define PACTEAM2_GAME_HPP

#include "Board.hpp"
#include "PacmanAgent.hpp"

class Game {
private:
    PacmanAgent* pacmanAgent;
    Board* board;
    int ticksPerSecond;
    int totalTicks;
    int ticksPerMovePlayer; //if the value is 1, it means the player moves every tick.
    int ticksPerMoveGhosts;
public:
    Game(std::string mapPath, int tPS, int ticksPlayer, int ticksGhosts, PacmanAgent* _pacmanAgent);
    void printBoard();
    void movePlayer();
    void update();
};

#endif //PACTEAM2_GAME_HPP
