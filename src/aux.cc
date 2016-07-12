#include "aux.h"


// Generador aleatorio
// Importamos el random desde Realea
int seed=time(NULL);
Random myrandom(new SRandom(seed));


int dimension;
int func_num;
int max_eval;
int num_ejecuciones = 25;
int dimensiones[2] = {10,30};
int population_size = 50;
int lbound = -100;
int ubound = 100;
double prob_restart = 0.1;
double prob_mutation = 0.001;
string type_ls = "sw";
//string type_ls = "cmaes";
//string type_ls = "simplex";
// Tamaño de las bolas cerradas en que busca la búsqueda local
double epsilon = 0.25;



double fitness(vector<double> x){
	double result;
	cec14_test_func(&x[0], &result, dimension, 1, func_num);
	return result;
}
