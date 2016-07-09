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

#ifndef _CMAESHANSEN_H 

#define _CMAESHANSEN_H 1

#include "ilocalsearch.h"
// #include "newutil.h"

#include "origcmaes.h"
#include "cmaes_interface.h"

namespace realea {

/**
 * @class CMAESHansen
 *
 * @brief Local Search method CMAESHansen defined by Hansen. 
 *
 * It has been reimplementated by Daniel Molina, from the implementation in  Matlab from Hansen
 */
class CMAESHansen : public ILocalSearch {
    public:
	/**
	 * Constructor
	 *
	 * @param fconfig file config
	 */
	CMAESHansen(string fconfig);
        /**
         * Select my current random seed when the LS is applied
         */
        void setMyRandom(void);
	/**
	 * Search in the total range
	 *
	 * @param factor ratio of search
	 */
	void searchRange(double factor);
	/**
	 * Search in the population neighbood
	 *
	 * @param factor ratio of search
	 */
	void searchNeighborhood(double ratio);
	unsigned apply(ILSParameters *opt, tChromosomeReal &sol, tFitness &fitness, unsigned itera);
	ILSParameters *getInitOptions(tChromosomeReal &sol);

    private:
	double m_rfactor;
	double m_nfactor;
	string m_fconfig;
	bool m_debug;
};


class CMAESHansenParams : public ILSParameters {
public:
    cmaes_t evo;
    double *xinit, *stddev;
    double *fitvals;   /* objective function values of sampled population */
    bool init;

    CMAESHansenParams(unsigned dim) {
	xinit = new double[dim];
	stddev = new double[dim];
	fitvals = NULL;
	init = false;
    }

    ~CMAESHansenParams(void) {
	delete[] xinit;
	delete[] stddev;
	cmaes_exit(&evo);
    }
};



class ProblemCMAESHansenEvalReal {
public:
    ProblemCMAESHansenEvalReal(IEval* eval) : m_eval(eval) {
    }

    tFitness eval(const double *sol, unsigned n) {
	 tChromosomeReal solv(n);

         for (unsigned i = 0; i < n; i++) {
	     solv[i] = sol[i];
         }
	 return m_eval->eval(solv);
   }

/*
    double eval(Real *sol, unsigned n) {
	 tChromosomeReal solv(n);

         for (unsigned i = 0; i < n; i++) {
	     solv[i] = sol[i];
         }
	 return m_eval->eval(solv);
   }
*/

private:
    IEval *m_eval;
};

}
#endif
