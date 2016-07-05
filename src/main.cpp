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
using namespace std;


// Parámetros del archivo con las funciones
void cec14_test_func(double *, double *,int,int,int);
double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


// Dimensión en la que estamos trabajando
int n = 10;
int func_num = 1;


double fitness(vector<double> x){
	double result;
	cec14_test_func(&x[0], &result, n, 1, func_num);
	return result;
}


int main(){
	// Fijamos la precisión de impresión
	std::cout << std::fixed;
    std::cout << std::setprecision(6);

	vector<double> x(n);

	for (int j = 0; j < n; j++)
		x[j]=0.0;


	for (int k = 0; k < 1; k++){
		cout << "f" << func_num << "(x[1]): " << fitness(x) << endl;
	}

	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
}
