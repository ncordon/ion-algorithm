#include "aux.h"


// Generador aleatorio
//int seed = std::chrono::system_clock::now().time_since_epoch().count();
//default_random_engine generator(seed);
//uniform_real_distribution<double> runif(0.0, 1.0);

// Importamos el random desde Realea
int seed=time(NULL);
Random myrandom(new SRandom(seed));


// Dimensión en la que estamos trabajando
int dimension;
int func_num;
int max_eval;
//int population_size = 50;
int population_size;
int lbound = -100;
int ubound = 100;
//double prob_restart = 0.1;
double prob_restart;
double prob_mutation = 0.001;
// Tamaño de las bolas cerradas en que busca la búsqueda local
double epsilon = 0.25;

double fitness(vector<double> x){
	double result;
	cec14_test_func(&x[0], &result, dimension, 1, func_num);
	return result;
}
