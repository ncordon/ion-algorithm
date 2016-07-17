#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "aux.h"
using namespace std;

/**
 * @class Solution
 * @brief Stores a n-tuple
 *
 */
class Solution: public std::vector<double>{
private:
    /*
     * @var fvalue Stores the fitness of the position
     */
    double fvalue;

public:
    /*
     * Position constructor
     * @param position n-tuple
     */
    Solution(vector<double> position);

    /*
     * Position and fit constructor
     * @param position n-tuple
     * @param fitness of the tuple
     */
    Solution(vector<double> position, double custom_fitness);

    /*
     * Empty default constructor
     */
    Solution();

    /*
     * Copy constructor
     * @param otro other solution tuple
     */
    Solution(Solution const &otro);

    /*
     * Updates the fitness of the solution
     */
    void updateFitness();

    /*
     * Set the fitness of the solution to a given value
     * @param score fitness of the tuple
     */
    void setFitness(double score);

    /*
     * Returns the fit of the solution
     * @return fvalue the fitness value
    */
    double getFitness();
};


#endif
