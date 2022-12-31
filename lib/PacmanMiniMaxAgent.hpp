#ifndef PACTEAM2_PACMANMINIMAXAGENT_HPP
#define PACTEAM2_PACMANMINIMAXAGENT_HPP

#include "Evaluation.hpp"
#include "PacmanAgent.hpp"
#include "EvaluationFunction.hpp"

class PacmanMiniMaxAgent : public PacmanAgent {
private:
    EvaluationFunction* ef;
public:
    PacmanMiniMaxAgent(EvaluationFunction* _ef);
    void updateState(Board* board);
    Evaluation minimax(Board* state, int depth, Evaluation alpha, Evaluation beta, bool maximizingPlayer);
};
#endif //PACTEAM2_PACMANMINIMAXAGENT_HPP
