#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "aux.h"
using namespace std;

class Solution: public std::vector<double>{
private:
    double fvalue;

public:
    Solution(vector<double> position);

    Solution(vector<double> position, double custom_fitness);

    Solution();

    Solution(Solution const &otro);

    void updateFitness();

    double getFitness();
};


#endif
