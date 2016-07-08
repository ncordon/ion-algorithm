#ifndef __ION_H__
#define __ION_H__

#include "aux.h"
using namespace std;

class Solution: public std::vector<double>{
private:
    double fvalue;

public:
    Ion(vector<double> position);

    Ion(vector<double> position, double custom_fitness);

    Ion();

    Ion(Ion const &otro);

    void updateFitness();

    double getFitness();
};


#endif
