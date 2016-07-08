#include "aux.h"

// Parámetros del archivo con las funciones
void cec14_test_func(double *, double *,int,int,int);
double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;




// Generador aleatorio
int seed = 12345678;
default_random_engine generator(seed);
uniform_real_distribution<double> runif(0.0, 1.0);
// Dimensión en la que estamos trabajando
int dimension = 10;
int func_num = 4;
int max_eval = 10000 * dimension;
int population_size = 30;
double prob_restart = 0.2;
double prob_mutation = 0.2;


double fitness(vector<double> x){
	double result;
	cec14_test_func(&x[0], &result, dimension, 1, func_num);
	return result;
}
