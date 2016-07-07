#ifndef __AUX_H__
#define __AUX_H__

#include <random>
#include <vector>
#include <iostream>
using namespace std;


// Parámetros del archivo con las funciones
extern void cec14_test_func(double *, double *,int,int,int);
extern double *OShift,*M,*y,*z,*x_bound;
extern int ini_flag,n_flag,func_flag,*SS;


// Generador aleatorio
extern int seed;
extern default_random_engine generator;
extern uniform_real_distribution<double> runif;
// Dimensión en la que estamos trabajando
extern int dimension;
extern int func_num;
extern int max_eval;
extern int population_size;
extern double prob_restart;
extern double fitness(vector<double> x);

#endif
