#include "solution.h"

Solution::Solution(vector<double> position) : vector(position){
    this->fvalue = fitness(position);
}

Solution::Solution(vector<double> position, double custom_fitness) : vector(position){
    this->fvalue = custom_fitness;
}

Solution::Solution(){}

Solution::Solution(Solution const &otro) : vector((vector<double>) otro){
    this->fvalue = fitness((vector<double>) otro);
}

void Solution::updateFitness(){
    fvalue = fitness(*this);
}

void Solution::setFitness(double score){
    fvalue = score;
}

double Solution::getFitness(){
    return fvalue;
}
