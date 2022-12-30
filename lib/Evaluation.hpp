#ifndef PACTEAM2_EVALUATION_HPP
#define PACTEAM2_EVALUATION_HPP

#include <vector>

struct Evaluation {
private:
    std::vector<int> ev_list;
public:
    Evaluation(std::vector<int> evaluations);
    Evaluation(int eval);
    int compare(Evaluation e2);
    int getEvaluation(int index);
};

#endif //PACTEAM2_EVALUATION_HPP
