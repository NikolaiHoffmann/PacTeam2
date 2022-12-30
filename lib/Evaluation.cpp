#include "Evaluation.hpp"
#include <iostream>

Evaluation::Evaluation(std::vector<int> evaluations) {
    ev_list = evaluations;
}

Evaluation::Evaluation(int eval) {
    std::vector<int> evals;
    evals.push_back(eval);
    ev_list = evals;
}


int Evaluation::compare(Evaluation e2) {
    std::vector<int>::iterator it1 = ev_list.begin();
    std::vector<int>::iterator it2 = e2.ev_list.begin();

    while ((it1 != ev_list.end()) && (it2 != e2.ev_list.end())) {
        int diff = *it1 - *it2;
        if (diff < 0) return -1;
        else if (diff > 0) return 1;
        else {
            it1++;
            it2++;
        }
    }
    if ((it1 == ev_list.end()) && (it2 == e2.ev_list.end())) {
        //it1 and it2 have same size
        return 0;
    }
    else if (it1 == ev_list.end()) {
        //it2 has more elements than it1
        return -1;
    }
    else return 1;
}

/*
bool operator == (const Evaluation& e) const {
	return !Compare(e);
}

bool operator < (const Evaluation& e) const {
	return Compare(e) < 0;
}

bool operator > (const Evaluation& e) const {
	return Compare(e) > 0;
}
*/

int Evaluation::getEvaluation(int index) {
    return ev_list[index];
}