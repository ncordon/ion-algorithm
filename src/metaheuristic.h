#ifndef __METAHEURISTIC_H__
#define __METAHEURISTIC_H__


#include <algorithm>
#include <iostream>
#include "solution.h"

using namespace realea;

/**
 * Updates the fitness of a population of ions
 *
 * @param population of iions
 * @param eval current evaluations number of the fitness function. Modified.
 */
void updateFitness(vector<Solution> &population, int &eval);

/**
 * Order function between two ions
 *
 * @param i first ion
 * @param j second ion
 * @return true if fitness(i) < fitness(j)
 */
bool ionOrder(Solution i, Solution j);


/**
 * Updates the location of ions
 *
 * @param current vector of anions/cation
 * @param reference best cation/anion
 */
void updateLocations(vector<Solution> &current, Solution reference);


/**
 * Normalize the ions in the search space
 *
 * @param ions vector to normalize
 * @returns the values of ions that fall outside the search space normalized
 *          to the frontier
 * @see normalize(Solution &ion)
 */
void normalize(vector<Solution> &ions);

/**
 * Normalize an ion in the search space
 *
 * @param ion ion to normalize
 * @returns the values of the ion that fall outside the search space normalized
 *          to the frontier, the rest of the values are not modified
 *
 */
void normalize(Solution &ion);

/**
 * Initializes a population of ions with values in the search space
 * @param ions vector of ions to initialize
 */
void initialize(vector<Solution> &ions);

/**
 * Restart values of ions
 * @param ions vector of cations/anions resp.
 * @param ref  best anion/cation resp.
 */
void redistribute(vector<Solution> &ions, Solution ref);

/**
 * Restart values of ions in solid phase of the algorithm
 * @param ions vector of cations/anions resp.
 * @param bests  vector of best values of cations/anions.
 * @see ionAlgorithm_v2()
 */
void redistribute(vector<Solution> &ions, vector<Solution> &bests);

/*
 * First version of the ion algorithm
 */
vector<double> ionAlgorithm();

/*
 * Modified version of algorithm
 */
vector<double> ionAlgorithm_v2();

/*
 * Updates the best solution found until the moment
 * @param best solution
 * @param ref posible new best solution
 */
bool updateBestSolution(Solution &best_solution, Solution ref);

/*
 * Applies the selected local search of Realea software to a solution
 * @param solution to apply the local search to
 * @param eval evaluations number to the moment
 * @param evals_ls maximum number of evaluations that can use the local search
 */
void applyRealeaLS(Solution &solution, int &eval, int evals_ls);

/**
 * Applies the own implemented local search to a solution
 * @param eval evaluations number to the moment
 * @param evals_ls number of evaluations that would use the local search
 */
void applyLocalSearch(Solution &solution, int &eval, int evals_ls);

/**
 * Computes the norm of a vector
 * @param real vector to which we want to compute the norm
 * @return norm of v
 */
double computeNorm(vector<double> v);

#endif
