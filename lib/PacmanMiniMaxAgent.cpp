#include "PacmanMiniMaxAgent.hpp"
#include "Evaluation.hpp"
#include <iostream>

PacmanMiniMaxAgent::PacmanMiniMaxAgent(EvaluationFunction* _ef) {
    ef = _ef;
}

//PacmanMiniMaxAgent::~PacmanMiniMaxAgent() {
//    delete[] ef;
//}

void PacmanMiniMaxAgent::updateState(Board* board) {
    Evaluation alpha = Evaluation(-9999999);
    Evaluation beta = Evaluation(9999999);
    std::vector<Board*> possibleStates = board->getPacmanChildStates();
    //int maxEval = INT_MIN;
    Evaluation maxEval = Evaluation(-9999999);
    Board* bestState = nullptr;
    std::vector<Board*>::iterator it = possibleStates.begin();
    for (; it != possibleStates.end(); ++it) {
        Board* currState = *it;
        Evaluation currStateValue = minimax(currState, 6, alpha, beta, false);
        if (currStateValue.compare(maxEval) > 0) {
            maxEval = currStateValue;
            bestState = currState;
        }
    }
    //for (it = possibleStates.begin(); it != possibleStates.end(); ++it) {
    //    Board* currState = *it;
    //    delete[] currState;
    //}

    //at this point, bestState contains the best possible next state for pacman

    Position currPos = board->getPacman()->getPosition();
    Position newPos = bestState->getPacman()->getPosition();
    Direction directionToTake = currPos.direction(newPos);
    board->changePlayerDirection(directionToTake);
    board->movePlayer();
}

Evaluation PacmanMiniMaxAgent::minimax(Board* state, int depth, Evaluation alpha, Evaluation beta, bool maximizingPlayer) {
    if (depth == 0 || state->isGameOver()) {
        return ef->evaluate(state);
    }

    if (maximizingPlayer) {
        Evaluation maxEval = Evaluation(-9999999);
        //int maxEval = INT_MIN;
        std::vector<Board*> possibleStates = state->getPacmanChildStates();
        std::vector<Board*>::iterator it = possibleStates.begin();
        for (; it != possibleStates.end(); ++it) {
            Board* currState = *it;
            Evaluation currStateValue = minimax(currState, depth - 1, alpha, beta, false);
            if (currStateValue.compare(maxEval) > 0) maxEval = currStateValue;
            if (alpha.compare(currStateValue) > 0) alpha = currStateValue;
            if (beta.compare(alpha) <= 0) break;
        }
        return maxEval;
    }
    else {
        Evaluation minEval = Evaluation(9999999);
        //int minEval = INT_MAX;
        std::vector<Board*> possibleStates = state->getGhostsChildStates();
        std::vector<Board*>::iterator it = possibleStates.begin();
        for (; it != possibleStates.end(); ++it) {
            Board* currState = *it;
            Evaluation currStateValue = minimax(currState, depth - 1, alpha, beta, true);
            if (currStateValue.compare(minEval) < 0) minEval = currStateValue;
            if (beta.compare(currStateValue) < 0) beta = currStateValue;
            if (beta.compare(alpha) <= 0) break;
        }
        return minEval;
    }
}