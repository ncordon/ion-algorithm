/*
CEC14 Test Function Suite for Single Objective Optimization
Jane Jing Liang (email: liangjing@zzu.edu.cn; liangjing@pmail.ntu.edu.cn)
Dec. 12th 2013
*/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "metaheuristic.h"
using namespace std;


int main(){
	int num_ejecuciones;
	int dimensiones[2] = {10,30};
	double suma;

	// Fijamos la precisión de impresión
	std::cout << std::fixed;
    std::cout << std::setprecision(6);

	for (int d = 0; d < 2; d++){
		dimension = dimensiones[d];
		cout << "Dimensión: " << dimension << endl;

		for(int f_num=4; f_num <= 4; f_num++){
			func_num = f_num;

			cout << "f" << f_num << " ";
			suma = 0;

			for (int i=0; i<25; i++){
				suma += (fitness(ion_algorithm()) - (func_num*100));
			}
		cout << suma/25 << endl;
		}
	}

	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
}
