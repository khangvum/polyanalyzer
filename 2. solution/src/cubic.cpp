/*! \file	    cubic.cpp
	\brief	    Definition for cubic equation solving function
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
#include <complex>
using namespace std;

namespace polyanalyzer {
	// Reference: https://mathcenter.oxford.emory.edu/site/math108/cubic/cubic_formula.png
	void Function::solve_cubic(double a, double b, double c, double d) {
		// Calculate the discriminants
		const double	delta_0{ pow(b, 2) - 3.0 * a * c },
			delta_1{ 2.0 * pow(b, 3) - 9.0 * a * b * c + 27.0 * pow(a, 2) * d };
		const complex<double>	delta{ format_complex(pow(delta_1, 2) - 4.0 * pow(delta_0, 3)) },
			C_plus{ format_complex(cbrt(1.0 / 2.0 * (delta_1 + sqrt(delta)))) },
			C_minus{ format_complex(cbrt(1.0 / 2.0 * (delta_1 - sqrt(delta)))) };

		// Calculate the roots based on the discriminants
		// - There will always be one real root
		const complex<double> x1{ format_complex(-1.0 / (3.0 * a) * (b + C_plus + C_minus)) };
		roots_.push_back(x1.real());

		// - The last two roots involve complex root of unity, only take the roots if they are real
		const complex<double>	x2{ format_complex(-1.0 / (3.0 * a) * (b - u_plus * C_plus - u_minus * C_minus)) },
			x3{ format_complex(-1.0 / (3.0 * a) * (b - u_minus * C_plus - u_plus * C_minus)) };

		if (abs(x2.imag()) < epsilon)
			roots_.push_back(x2.real());
		if (abs(x3.imag()) < epsilon)
			roots_.push_back(x3.real());
	}
}	// End of namespace polyanalyzer