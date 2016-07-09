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

using namespace realea;

void getInitRandom(Random *random, DomainRealPtr domain, tChromosomeReal &crom) {
  tReal min, max;
    
  for (unsigned i = 0; i < crom.size(); ++i) {
      domain->getValues(i, &min, &max, true);
      crom[i] = random->randreal(min, max);
  }

}

int main(int argc, char *argv[]) {
  int dim = 10;
  int fun = 1;
  int maxevals = 0;
  DomainRealPtr domain;
  ILocalSearch *ls;
  ILSParameters *ls_options;
  // It is a vector value
  tChromosomeReal sol(dim);
  ProblemCEC2014 cec2014(dim);
  string type_ls="sw";

  // Init the random with the seed
  int seed=time(NULL);
  Random random(new SRandom(seed));

  if (argc > 1) {
     type_ls = argv[1];
     assert(type_ls == "sw" || type_ls == "simplex" || type_ls == "cmaes");
  }
	
  // Get the function fun for dimension dim
  ProblemPtr problem = cec2014.get(fun);
  // Domain is useful for clipping solutions
  domain = problem->getDomain();
  // Init the initial solution (for LS)
  getInitRandom(&random, domain, sol);
  // Get the maximum evaluations from the problem
  unsigned max_evals = problem->getMaxEval();

  if (type_ls == "sw") {
     // Get the Solis Wets problem
     SolisWets *sw = new SolisWets();
     // Set the delta values
     sw->setDelta(0.2);
     ls = sw;
  }
  else if (type_ls == "simplex") {
    ls = new SimplexDim();
  }
  else if (type_ls == "cmaes") {
    CMAESHansen *cmaes = new CMAESHansen("cmaesinit.par");
    cmaes->searchRange(0.1);
    ls = cmaes;
  }

  cout <<"Applying the '" <<type_ls <<"' LS" <<endl;
  
  // The following options are common for all LS methods
  // Set the problem to allow the LS to eval solutions
  ls->setProblem(problem.get());
  // Set the random to generate mutations
  ls->setRandom(&random);
  // Get the initial parameters
  ls_options = ls->getInitOptions(sol);
  // Set the maximum and minimum delta for the LS
  // (init with the maximum delta value

  // Test with 10% of evaluations
  unsigned evals_ls = 0.2*max_evals;

  // Eval the initial solution
  tFitness fitness = problem->eval(sol);
  tFitness before, after, diff;

  before = fitness;
  
  // sol and fitness are updated
  unsigned evals = ls->apply(ls_options, sol, fitness, evals_ls);
  // evals should be equals to evals_ls
  if (evals_ls != evals) {
    cout <<"Max Evals " <<evals_ls <<", real evals " <<evals <<endl;
  }

  after = fitness;
  assert(!problem->isBetter(before, after));
  diff = before-after;
  cout <<"Improvement: " <<std::scientific <<before <<" -> " <<std::scientific <<after;
  cout <<" [" <<std::scientific <<diff <<"]" <<endl;
  
  return 0;
}

