#ifndef __IMPROVEMENT_H__
#define __IMPROVEMENT_H__


#include <algorithm>
#include <iostream>
#include "solution.h"

using namespace realea;


void updateFitness(vector<Solution> &population, int &eval);

bool ionOrder(Solution i, Solution j);

void updateLocations(vector<Solution> &current, Solution reference);

void normalize(vector<Solution> &ions);

void normalize(Solution &ion);

void initialize(vector<Solution> &ions);

void redistribute(vector<Solution> &ions, Solution ref);

vector<double> ion_algorithm();

bool updateBestSolution(Solution &best_solution, Solution ref);

void applyRealeaLS(Solution &solution, int &eval, int evals_ls);

#endif
