#pragma once
/*! \file	    Function.cpp
	\brief	    Function class definition
	\author	    Khang Vu
	\date	    2024-12-21
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2024.12.21
	  Directory hierarchy cleamup
	  Separated system, constants, and helper utilities

  Version 2024.05.05
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/Function.hpp"
#include "../../0. utilities/utilities.hpp"
#include <algorithm>
using namespace std;

namespace polyanalyzer {
	// Methods
	void Function::solve() {
		auto [a, b, c, d, e] { coefficients_ };

		// Solve the function
		if (abs(a) > epsilon)
			solve_quartic(a, b, c, d, e);
		else if (abs(b) > epsilon)
			solve_cubic(b, c, d, e);
		else if (abs(c) > epsilon)
			solve_quadratic(c, d, e);
		else
			solve_linear(d, e);

		// Sort the roots and remove duplicates
		sort(begin(roots_), end(roots_));
		roots_.erase(unique(begin(roots_), end(roots_)), end(roots_));
	}

	Function Function::derivative() const {
		array<double, 5> deri_coefficients{};

		for (size_t i{ 0 }; i < deri_coefficients.size() - 1; ++i)
			deri_coefficients[i + 1] = coefficients_[i] * (coefficients_.size() - i - 1);

		return Function(deri_coefficients);
	}
}	// End of namespace polyanalyzer