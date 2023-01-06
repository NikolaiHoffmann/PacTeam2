#ifndef PACTEAM2_PACMANAGENT_HPP
#define PACTEAM2_PACMANAGENT_HPP

#include "Board.hpp"

class PacmanAgent {
public:
    virtual void updateState(Board* board) = 0;
    virtual ~PacmanAgent();
};

#endif //PACTEAM2_PACMANAGENT_HPP
