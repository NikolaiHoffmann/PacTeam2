#ifndef PACTEAM2_EVALUATIONFUNCTION_HPP
#define PACTEAM2_EVALUATIONFUNCTION_HPP

#include "Board.hpp"
#include "Evaluation.hpp"

class EvaluationFunction {
public:
    static Evaluation evaluate(Board* board);
};

#endif //PACTEAM2_EVALUATIONFUNCTION_HPP
