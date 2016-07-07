#ifndef __ION_H__
#define __ION_H__

#include "aux.h"
using namespace std;

class Ion: public std::vector<double>{
private:
    double fvalue;

public:
    Ion(std::vector<double> position);

    Ion();

    void updateFitness();

    double getFitness();
};


#endif
