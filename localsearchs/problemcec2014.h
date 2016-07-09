/**
 * Copyright 2014, Daniel Molina Cabrera <danimolina@gmail.com>
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
#ifndef PROBLEMCEC2014_H
#define PROBLEMCEC2014_H

#include "problem.h"
#include "problemcec2014.h"

namespace realea {

/**
 * This class allow us to use the benchmark for CEC'2014 Special Session in Real Optimization.
 * It wraps the original source code of the authors (version in C).
 */
class ProblemCEC2014 
{
public:
    /**
     * Set the object with the dimensionality.
     *
     * @param dim dimension
     */
    ProblemCEC2014(unsigned int dim);
    /**
     * Clear the memory
     */
    ~ProblemCEC2014();
    /**
     * Get the problem definition
     *
     * @param fn function integer (between 1 and 28).
     * @return the problem definition.
     */
    ProblemPtr get(unsigned int fn);

private:
    unsigned int m_dim;
    unsigned int m_fun;
};

}

#endif // PROBLEMCEC2014_H
