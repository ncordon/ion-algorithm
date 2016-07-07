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
	// Fijamos la precisión de impresión
	std::cout << std::fixed;
    std::cout << std::setprecision(6);


	cout << fitness(ion_algorithm()) << endl;


	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
}
