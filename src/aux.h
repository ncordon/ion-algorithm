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


// Generador aleatorio
extern Random myrandom;


// Dimensión en la que estamos trabajando
extern int dimension;
// Número de función que se ejecutará
extern int func_num;
// Número máximo de evaluaciones
extern int max_eval;
// Tamaño de la población de iones
extern int population_size;
// Probabilidad de reinicio de soluciones
extern double prob_restart;
// Probabilidad de mutación de soluciones
extern double prob_mutation;
// Radio de bolas que se considerarán en búsqueda local (applyLocalSearch)
extern double epsilon;
// Límites inferior y superior del espacio de búsqueda
extern int lbound;
extern int ubound;
// Número de ejecuciones para cada función
extern int num_ejecuciones;
extern int dimensiones[2];
// Tipo de búsqueda local a considerar
extern string type_ls;
// Función de fitness
extern double fitness(vector<double> x);

#endif
