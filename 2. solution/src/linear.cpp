/*! \file	    linear.cpp
	\brief	    Definition for linear equation solving function
	\author	    Manh Khang Vu
	\date	    2024-12-21
	\copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2024.12.21
	  Directory hierarchy cleamup
	  Separated system, constants, and helper utilities

  Version 2024.05.05
	  Alpha release

  =============================================================

  Copyright Manh Khang Vu

  ============================================================= */

#include "../inc/Function.hpp"
#include "../../0. utilities/utilities.hpp"
#include <cmath>
using namespace std;

namespace polyanalyzer {
	void Function::solve_linear(double a, double b) {
		if (abs(a) < epsilon)
			return;

		roots_.push_back(-b / a);
	}
}	// End of namespace polyanalyzer