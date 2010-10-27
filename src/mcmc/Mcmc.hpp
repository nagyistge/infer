/*************************************************************************
 *  ./src/mcmc/Mcmc.hpp
 *  Copyright Chris Jewell <chrism0dwk@gmail.com> 2012
 *
 *  This file is part of InFER.
 *
 *  InFER is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  InFER is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with InFER.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

/* Header file for aifuncs.cpp */

#ifndef INCLUDE_MCMC_H
#define INCLUDE_MCMC_H

#include <math.h>
#include <limits>


#include "SpatPointPop.hpp"
#include "Data.hpp"
#include "Parameter.hpp"

#define NEGINF (-numeric_limits<double>::infinity())

using namespace std;
using namespace EpiRisk;


struct Parameters
{
  Parameter beta1;
  Parameter beta2;
  Parameter phi;

  Parameters(const double beta1, const double beta2, const double phi) : beta1(beta1,Prior()),
                                                                         beta2(beta2,Prior()),
                                                                         phi(phi,Prior())
  { }

  Parameters(Parameters& toCopy) :  beta1(toCopy.beta1),
                                    beta2(toCopy.beta2),
                                    phi(toCopy.phi)
  { }

  virtual
  ~Parameters()
  { }
};


class Mcmc {

  Population<TestCovars>& pop_;
  Parameters& params_;
  double logLikelihood_;

  virtual
  double
  beta(const Population<TestCovars>::Individual& i, const Population<TestCovars>::Individual& j) const;
  virtual
  double
  betastar(const Population<TestCovars>::Individual& i, const Population<TestCovars>::Individual& j) const;
  void
  calcLogLikelihood();
  void
  updateTrans();
  void
  updateI(const size_t index);

public:
  Mcmc(Population<TestCovars>& population, Parameters& parameters);
  ~Mcmc();
  double
  getLogLikelihood() const;
  void
  run(const size_t numIterations);
};

#endif
