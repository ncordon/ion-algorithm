#include "aux.h"


// Generador aleatorio
int seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_real_distribution<double> runif(0.0, 1.0);

// Dimensión en la que estamos trabajando
int dimension = 10;
int func_num = 1;
int max_eval = 10000 * dimension;
int population_size = 50;
int lbound = -100;
int ubound = 100;
double prob_restart = 0.1;
double prob_mutation = 0.001;
double epsilon = 0.25;

double fitness(vector<double> x){
	double result;
	cec14_test_func(&x[0], &result, dimension, 1, func_num);
	return result;
}
