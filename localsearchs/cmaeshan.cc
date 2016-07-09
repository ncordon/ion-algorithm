/**
 * Copyright 2008, Daniel Molina Cabrera <danimolina@gmail.com>
 * 
 * This file is part of software Realea
 * 
 * Realea is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Realea is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cmaeshan.h"
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace realea;

typedef vector<tGen> DistVector;

DomainRealPtr m_domain=NULL;

CMAESHansen::CMAESHansen(string fconfig) : m_debug(false) {
	m_rfactor = 0;
	m_nfactor = 0;
	m_fconfig = fconfig;
}

/**
 * Obtain the range (max[0]-min[0], max[1]-min[1], ..., max[N-1]-min[N-1])
 *
 * @param domain
 *
 * @param range output
 */
static void getRange(DomainRealPtr domain, vector<tGen> *range) {
	tReal min, max;
	unsigned ndim = domain->getDimension();

	for (unsigned i = 0; i < ndim; i++) {
		domain->getValues(0, &min, &max);
		(*range)[i] = max-min;
	}
}


void CMAESHansen::searchRange(double factor) {
	assert(factor > 0 && factor <= 1);
}

ILSParameters *CMAESHansen::getInitOptions(tChromosomeReal &sol) {
    int i, dim = sol.size();
    CMAESHansenParams *param;
    DistVector dist(dim);

   param = new CMAESHansenParams(dim);

   for (i = 0; i < dim; i++) {
      param->xinit[i] = sol[i];
   }

   if (true) {
	DomainRealPtr domain = m_problem->getDomain();
	vector<tGen> range(dim);
	getRange(domain, &range);

	for (i = 0; i < dim; i++) {
	    param->stddev[i] = range[i]*m_rfactor+0.01;
	}
   }

   return param;
}
    

unsigned CMAESHansen::apply(ILSParameters *opt, tChromosomeReal &sol, tFitness &fitness, unsigned itera) {
   CMAESHansenParams *params = (CMAESHansenParams *) opt;
  double *const*pop; /* sampled population */
   unsigned dim;
  tFitness bestfit,oldbestfit;
   int lambda = 0, counteval = 0;
  tFitness fbestever=0;
  double *xbestever=NULL; /* store best solution */
  double fmean;
  const double *xmean; 
   // User defined input parameters (need to be edited)
   char const * stop=NULL; /* stop message */
   int maxeval = itera-lambda;
   DomainRealPtr domain = m_problem->getDomain();

   //---------- BEGIN CMAESC ------------------------------------------
   ProblemCMAESHansenEvalReal *eval = new ProblemCMAESHansenEvalReal(m_eval);
   dim = sol.size();

   if (!params->init) {
      params->fitvals = cmaes_init(&params->evo, dim, params->xinit, params->stddev, 0, 0, m_fconfig.c_str()); /* allocs fitvals */
      params->init = true;
   }

   lambda = cmaes_Get(&params->evo, "lambda");   /* needed for the restart */
   maxeval = itera-lambda;

   bestfit = 0;
   params->evo.countevals = 0; /* a hack, effects the output and termination */

   while(!(stop=cmaes_TestForTermination(&params->evo)) && counteval < maxeval) {
    	  /* Generate population of new candidate solutions */
	  pop = cmaes_SamplePopulation(&params->evo); /* do not change content of pop */

	  /* Here optionally handle constraints etc. on pop. You may
	   * call cmaes_ReSampleSingle(&params->evo, i) to resample the i-th
	   * vector pop[i], see below.  Do not change pop in any other
	   * way. You may also copy and modify (repair) pop[i] only
	   * for the evaluation of the fitness function and consider
	   * adding a penalty depending on the size of the
	   * modification.
	   */
 	  oldbestfit = bestfit;
	  
	  /* Compute fitness value for each candidate solution */
	  for (int i = 0; i < cmaes_Get(&params->evo, "popsize"); ++i) {
	    /* You may resample the solution i until it lies within the
	       feasible domain here, e.g. until it satisfies given  
               box constraints (variable boundaries). The function 
               is_feasible() needs to be user-defined.  
	       Assumptions: the feasible domain is convex, the optimum
	       is not on (or very close to) the domain boundary,
	       initialX is feasible and initialStandardDeviations are
	       sufficiently small to prevent quasi-infinite looping.
	    */
	    /* while (!is_feasible(pop[i])) 
	         cmaes_ReSampleSingle(&params->evo, i); 
	    */
	    params->fitvals[i] = eval->eval(pop[i], dim); 
	    counteval++;

	    if (params->fitvals[i] < bestfit || counteval == 1) {
		bestfit = params->fitvals[i];
	    }
	  }

	  /* update search distribution */
	  cmaes_UpdateDistribution(&params->evo, params->fitvals); 
	  
	  /* read control signals for output and termination */
//	  cmaes_ReadSignals(&params->evo, "signals.par"); /* from file signals.par */
	  
	  fflush(stdout);
	  params->evo.countevals = counteval;     /* ditto */
	} /* while !cmaes_TestForTermination(&params->evo) */

	fbestever = cmaes_Get(&params->evo, "fbestever"); 

	xbestever = cmaes_GetInto(&params->evo, "xbestever", xbestever); /* alloc mem if needed */
      
	/* best estimator for the optimum is xmean, therefore check */
	xmean = cmaes_GetPtr(&params->evo, "xmean");

	if (counteval == 0) {
	    if (stop != NULL) {
		printf("%s", stop);
	    }

	    if (fbestever) {
	    	copy(xbestever, xbestever+dim, sol.begin());
	    	fitness = fbestever;
	    }
	    delete eval;
	    return counteval;
	}


      if ((fmean = eval->eval(xmean, dim)) < fbestever) {
	fbestever = fmean;
	xbestever = cmaes_GetInto(&params->evo, "xmean", xbestever);
      }

      if (fbestever < fitness) {
	copy(xbestever, xbestever+dim, sol.begin());
	fitness = fbestever;
      }

      delete eval;
      return counteval;
}
