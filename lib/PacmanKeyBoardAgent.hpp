#ifndef PACTEAM2_PACMANKEYBOARDAGENT_HPP
#define PACTEAM2_PACMANKEYBOARDAGENT_HPP

#include "PacmanAgent.hpp"

class PacmanKeyBoardAgent : public PacmanAgent {
    void updateState(Board* board) final;
};

#endif //PACTEAM2_PACMANKEYBOARDAGENT_HPP
