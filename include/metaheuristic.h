#ifndef __METAHEURISTIC_H__
#define __METAHEURISTIC_H__


#include <algorithm>
#include "ion.h"
using namespace std;


void updateFitness(vector<Ion> &population);

bool ionOrder(Ion i, Ion j);

void updateLocations(vector<Ion> &current, Ion reference);

void normalize(vector<Ion> &ions, double lbound, double ubound);

void initialize(vector<Ion> &ions, int lbound, int ubound);

void redistribute(vector<Ion> &ions, Ion ref,
                  double lbound, double ubound);

vector<double> ion_algorithm();

#endif
