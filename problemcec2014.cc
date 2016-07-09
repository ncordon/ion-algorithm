#include "problemcec2014.h"
#include <cstdlib>
#include <cstdio>
#include <cassert>

using namespace realea;

extern void cec14_test_func(double *, double *,int,int,int);

double *OShift=NULL,*M=NULL,*y=NULL,*z=NULL,*x_bound=NULL;
int ini_flag=0,n_flag,func_flag,*SS=NULL;

ProblemCEC2014::ProblemCEC2014(unsigned int dim) {
    assert(dim == 10 || dim == 30 || dim == 50);
    m_dim = dim;
}

ProblemCEC2014::~ProblemCEC2014() {
  if (y) {
	free(y);
   }
   if (z) {
	free(z);
   }
   if (M) {
	free(M);
   }
   if (OShift) {
	free(OShift);
   }
   if (x_bound) {
	free(x_bound);
   }
   if (SS) {
	free(SS);
   }

}


static int m_fn;

tFitness eval_probcec2014(const tGen *x, int dim) {
    double fitness;

    cec14_test_func( (double *)x, &fitness, dim, 1, m_fn);
//    printf("Resultado de evaluar: %e\n", fitness);
    return fitness;
}

ProblemPtr ProblemCEC2014::get(unsigned int fn) {
    // Check the number
    assert(fn >= 1 && fn <= 30);
    // tGen must be double
    assert(sizeof(tGen)==sizeof(double));
    assert(sizeof(tFitness)==sizeof(double));
    m_fn = fn;
    unsigned m_ndim = m_dim;

    ProblemPtr prob (new Problem());
    prob->setDimension(m_ndim);

    // All functions are [-100, 100]
    for (unsigned i = 0; i < m_ndim; ++i) {
        prob->setDomainValues(i, -100, 100, true);
    }

    // Bias is fn*10 (100 for f1, 200 for f2, ...)
    prob->setOptimize(fn*100, 1e-8);
    // Numevals = 10000*
    prob->setMaxEval(10000*m_ndim);
    prob->setMinimize();

    // Defino la función de fitness
    prob->setEval(eval_probcec2014);
    DomainRealPtr domain = prob->getDomain();
    domain->setBounds();
    return prob;
}
