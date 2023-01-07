#ifndef PACTEAM2_GAME_HPP
#define PACTEAM2_GAME_HPP

#include "Board.hpp"
#include "PacmanAgent.hpp"

class Game {
private:
    PacmanAgent* pacmanAgent;
    Board* board;

public:
    Game() = default;
    Game(const std::string& mapPath, PacmanAgent* _pacmanAgent);
    ~Game();
    void printBoard();
    bool update();
    int elapsedGameTicks();
};

#endif //PACTEAM2_GAME_HPP
