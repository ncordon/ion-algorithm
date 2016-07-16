#ifndef __AUX_H__
#define __AUX_H__

#include <vector>
#include "problemcec2014.h"
#include "problem.h"
#include "solis.h"
#include "simplex.h"
#include "cmaeshan.h"
#include "random.h"
#include "srandom.h"
#include "domain.h"
#include "localsearch.h"
#include <iostream>
#include <string>
using namespace realea;


// Parámetros del archivo con las funciones
extern void cec14_test_func(double *, double *,int,int,int);
extern double *OShift,*M,*y,*z,*x_bound;
extern int ini_flag,n_flag,func_flag,*SS;


/// Random generator
extern Random myrandom;


/// Dimension we are working at
extern int dimension;
/// Function to benchmark
extern int func_num;
/// Maximum evaluation number
extern int max_eval;
/// Size of ions population
extern int population_size;
/// Solutions restart probability
extern double prob_restart;
/// Solutions mutations probability
extern double prob_mutation;
/// Radius of sets in which we apply local search.
extern double epsilon;
/// Lower bound of [lbound,ubound]^D search space
extern int lbound;
/// Upper bound of [lbound,ubound]^D search space
extern int ubound;
/// Number of executions the algorithm with a given function
extern int num_ejecuciones;
/// 10 and 30, dimensions to benchmark
extern int dimensiones[2];
/// Type of local search to apply
extern string type_ls;
/// Fitness function
extern double fitness(vector<double> x);

#endif
