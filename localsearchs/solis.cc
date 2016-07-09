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

#include "solis.h"
#include "random.h"
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace realea;

class SolisParams : public ILSParameters {
   public:
       SolisParams(unsigned dim) : bias(dim) {
       }
       unsigned dim(void) {
	  return bias.size();
       }

       double delta;
       vector<double> bias;
       unsigned numFailed;
       unsigned numSuccess;
       virtual ~SolisParams(void) {}
};


SolisWets::SolisWets(void) {
    m_maxdelta = m_mindelta = -1;
}

void SolisWets::setDelta(double maxdelta) {
   assert(maxdelta > 0); 
   m_maxdelta = maxdelta;
}

void SolisWets::setDelta(double mindelta, double maxdelta) {
    assert(mindelta > 0 && mindelta <= maxdelta);
    m_mindelta = mindelta;
    m_maxdelta = maxdelta;
}

ILSParameters *SolisWets::getInitOptions(tChromosomeReal &sol) {
    SolisParams *option;
    unsigned dim = m_problem->getDimension();
    option = new SolisParams(dim);
    option->numFailed = option->numSuccess = 0;
    unsigned nearest;
    
    assert(m_maxdelta > 0);
    option->delta = m_maxdelta;

    fill(option->bias.begin(), option->bias.end(), 0.0);
    
    return ((ILSParameters *) option);
}

tFitness SolisWets::getNeighbour(ILSParameters *param, tChromosomeReal &actual, tChromosomeReal &dif, tChromosomeReal &newsol) {
    unsigned i;
    SolisParams *p = (SolisParams *) param;
    unsigned ndim = actual.size();
    DomainRealPtr domain = m_problem->getDomain();

    for (i = 0; i < ndim; i++) {
        if (domain->canBeChanged(i)) {
	    dif[i] = m_random->normal(p->delta);
	    newsol[i] = actual[i] + p->bias[i] + dif[i];
	}
	else 
	   newsol[i] = actual[i];
    }

    domain->clip(newsol);
    return m_eval->eval(newsol);
}



static double increm_bias(const double &bias, const double &dif) {
    return 0.2*bias+0.4*(dif+bias);
}

static double dec_bias(const double &bias, const double &dif) {
    return bias-0.4*(dif+bias);
}

unsigned SolisWets::apply(ILSParameters *params, tChromosomeReal &sol, tFitness &sol_perf, unsigned maxeval) {
   SolisParams *p = (SolisParams *) params;
   unsigned ndim = sol.size();
   tChromosomeReal dif(ndim), newsol(ndim);
   DomainRealPtr domain = m_problem->getDomain();
   tFitness newsol_perf;
   unsigned gen;
   unsigned numEval = 0;

   for (numEval = 0; numEval < maxeval; ) {
      newsol_perf = getNeighbour(p, sol, dif, newsol);
      numEval++;

      // Si lo mejoro lo copio
      if (m_problem->isBetter(newsol_perf, sol_perf) ) {
	 copy(newsol.begin(), newsol.end(), sol.begin());
	 sol_perf = newsol_perf;

	 // Adapto bias 
	 transform(p->bias.begin(), p->bias.end(), dif.begin(), p->bias.begin(), 
		     ptr_fun(increm_bias));
	 p->numSuccess++;
	 p->numFailed = 0;
      }
      else if (numEval < maxeval && !m_problem->isBetter(newsol_perf, sol_perf)) {
	 // Invierto la dirección
	 for (gen = 0; gen < ndim; gen++) {
	    newsol[gen] = sol[gen] - p->bias[gen] - dif[gen];
	 }

	 domain->clip(newsol);
	 newsol_perf = m_eval->eval(newsol);
	 numEval++;

	 if (m_problem->isBetter(newsol_perf, sol_perf)) {
	    copy(newsol.begin(), newsol.end(), sol.begin());
	    sol_perf = newsol_perf;

	    // Disminuyo bias
	    transform(p->bias.begin(), p->bias.end(), dif.begin(), p->bias.begin(), 
			ptr_fun(dec_bias));

	    p->numSuccess++;
	    p->numFailed = 0;
	 }
	 else {
	    // Se reduce bias a la mitad
	    transform(p->bias.begin(), p->bias.end(), p->bias.begin(), 
			bind2nd(multiplies<double>(), 0.5));
	    p->numFailed++;
	    p->numSuccess = 0;
	 }

      }

      if (p->numSuccess >= maxSuccess) {
	 p->numSuccess = 0;
	 p->delta *= 2;
      }
      else if (p->numFailed >= maxFailed) {
	 p->numFailed = 0;
	 p->delta *= 0.5;
      }

   } // De comprobar las iteraciones

   return numEval;
}
