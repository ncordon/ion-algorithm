#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "metaheuristic.h"
using namespace std;


int main(){
	double suma;
	double current_result;

	// Fijamos la precisión de impresión
	std::cout << std::fixed;
    std::cout << std::setprecision(6);


	for (int d = 0; d < 2; d++){
		dimension = dimensiones[d];
		max_eval = 10000 * dimension;
		cout << "Dimensión: " << dimension << endl;

		for(int f_num=1; f_num <= 20; f_num++){
			func_num = f_num;
			cout << "f" << f_num << ", ";
			suma = 0;

			for (int i=0; i < num_ejecuciones; i++){
				current_result =  fitness(ionAlgorithm()) - (func_num*100);
				suma += current_result;
			}

			cout << suma/num_ejecuciones << endl;
		}
	}

	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
}
