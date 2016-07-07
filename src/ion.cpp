#include "ion.h"

Ion::Ion(vector<double> position) : vector(position){
    this->fvalue = fitness(position);
}

Ion::Ion(){}


void Ion::updateFitness(){
    fvalue = fitness(*this);
}

double Ion::getFitness(){
    return fvalue;
}
