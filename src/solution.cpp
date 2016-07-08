#include "ion.h"

Solution::Ion(vector<double> position) : vector(position){
    this->fvalue = fitness(position);
}

Solution::Ion(vector<double> position, double custom_fitness) : vector(position){
    this->fvalue = custom_fitness;
}

Solution::Ion(){}

Solution::Ion(Ion const &otro) : vector((vector<double>) otro){
    this->fvalue = fitness((vector<double>) otro);
}

void Solution::updateFitness(){
    fvalue = fitness(*this);
}

double Solution::getFitness(){
    return fvalue;
}
