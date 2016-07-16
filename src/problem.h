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

#ifndef _CONFIGPROGRAM_

#define _CONFIGPROGRAM_ 1

#include "signal.h"
#include "domain.h"
#include "define.h"

#include <string>
#include <stdexcept>
#include <memory>
#include <memory>

using namespace std;

namespace realea {

/**
 * @class OptimeCriterion
 * @ingroup realea_common
 *
 * @brief Let specify when a class is optimum.
 *
 * This class' target is easier to specify when the optimum is achieved
 * 
 */
#define MINIMIZE minimize
#define MAXIMIZE maximize
struct OptimeCriterion { 
public:

   /**
    * Constructor.
    *
    * @param optime optimum value
    * @param dif threshold value
    */
   OptimeCriterion(double optime, double dif);
   /**
    * Set the threshold required to identify two solution are equivalent
    * @param dif diference value
    */
   void setThreshold(double dif);

   /**
    * @return the threshold
    */
   inline double getThreshold(void);

    /**
     * Check if the fitness is too close to optimum
     *
     * @param fitness fitness of current solution
     * @return true if abs(fitness - fitness_optimum) < threshold
     */
    bool isOptime(double fitness); 

	/**
	 * Set the minimize criterion
	 */
    void setMinimize(void) {
	m_minimize = true;
    }
	/**
	 * Set the minimize criterion
	 */
    void setMaximize(void) {
        m_minimize = false;
    }

    bool minimize(void) {
	return m_minimize;
    }

    bool maximize(void) {
	return !m_minimize;
    }


   /**
    * return if fitness value1 is better than value2
    *
    * @param value1
    * @param value2
    * @return true if value is better than value2
    */
   bool isBetter(double value1, double value2) {
       if (m_minimize) {
          return (value1 < value2);
       }
       else {
          return (value1 > value2);
	}

}

   double getOptime(void) {
	return m_optime;
   }

private:
   double m_optime;
   double m_threshold; /**< Threshold value */
   double m_minimize;
};
	

class ConfigException: public runtime_error {
private:
	string m_name;

public:
	ConfigException(string name) : runtime_error(name) {
		m_name = name;
	}

public:
	virtual ~ConfigException(void) throw () { }
	virtual const char *what(void) {
		string msg;
		msg = "Parameter Config " +m_name +" is not yet defined";
		return msg.c_str();
	}
};

typedef tFitness (*tEval)(const tGen *x, int dim);
typedef void (*tAfterEvalFunction)(const tGen *x, int dim, tFitness fitness);

/**
 * @class Problem
 *
 * @brief This class represent a problem to be resolved
 *
 * To apply the EA to new problems, a subclass of ProblemFactory must be defined, and it must
 * return an adequated initialized problem (instance of this class)
 *
 * @see ProblemFactory
 */
 class Problem: public IEval {
public:
	/**
	 * Destructor
	 */
	virtual ~Problem(void);
	/**
	 * Constructor
	 */
	Problem(void); 

	/**
	 * Set the function evaluation. It is a function that return a tFitness from a Chromosome real
	 * typedef tFitness (*tEval)(const tGen *x, int dim)
	 *
	 * @param eval Evaluation function.
	 */
	void setEval(tEval eval);

	/**
	 * Set the minimize criterion
	 */
	void setMinimize(void);
	/**
	 * Set the minimize criterion
	 */
	void setMaximize(void);
	/**
	 * @return true if it is a minimization problem
	 */
	bool minimize(void);
	/**
	 * @return true if it is a maximization problem
	 */
	bool maximize(void);
	/**
	 * @return true value1 is better than value2 in the problem
	 */
	bool isBetter(tFitness x, tFitness y);

	/**
	 * Set the problem's dimensionality 
	 *
	 * @param dim new dimensionality
	 */
	void setDimension(unsigned int dim);
	/**
	 * @return the dimensionality of current problem
	 */
	virtual unsigned int getDimension(void);
	
	/**
	 * Set for a gen the range (maximum and minimum values)
	 *
	 * @param gen pos of current gen to set (from 0..getDimension()-1)
	 * @param min minimum value
	 * @param max maximum value
	 * @param check set if the gen must be checked, default true
	 */
	void setDomainValues(unsigned int gen, tGen min, tGen max, bool check=true);
	
	/**
	 * Set the optimum value and the threshold
	 * A solution is an optimum if their difference in fitness with the optimum 
	 * is lower than this threshould (if it is not defined, threshold is equal to 0)

	 * @param optime optimum value
	 * @param threshold threshold value (must be positive)
	 */
	void setOptimize(tFitness optime, double threshold); 

	/**
	 * Set the threshold, a solution is an optimum if their difference in fitness with the optimum 
	 * is lower than this threshould (if it is not defined, threshold is equal to 0)
	 *
	 * @param dif threshold value (must be positive)
	 *
	 */
	void setThreshold(double dif);

	/**
	 * Set the maximum evaluation number for the problem
	 *
	 * @param maxeval maximum eval number
	 */
	void setMaxEval(unsigned int maxeval); 

	/**
	 * @return the maximum evaluation number
	 */
	unsigned getMaxEval(void);


	/**
	 * @return the domain of the problem
	 */
	virtual DomainRealPtr getDomain(void);
	/**
	 * @return the optime value
	 */
	tFitness getOptime(void);

	unsigned getMaxEval(unsigned max);

	tFitness eval(const tChromosomeReal &sol);
	tFitness eval(const tGen *sol, int dim);
	void copy(Problem *problem); 

protected:
	OptimeCriterion *m_checkOptime;
        DomainRealPtr m_domain;
	unsigned m_maxeval;
	tEval m_eval;
	tAfterEvalFunction m_notify;
};

typedef auto_ptr<Problem> ProblemPtr;
typedef ProblemPtr& ProblemParamPtr;



void setProblem(Problem* &prob);
Problem* getProblem(void);
}

#endif
