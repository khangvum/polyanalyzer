/*! \file	    quartic.cpp
	\brief	    Definition for quartic equation solving function
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
#include <cmath>
#include <complex>
using namespace std;

// Reference: https://mathworld.wolfram.com/QuarticFormula.html
void Function::solve_quartic(double a, double b, double c, double d, double e) {
	// Ensure that the quartic equation is monic
	b /= a, c /= a, d /= a, e /= a, a = 1.0;

	// Solve the quartic equation by solving a resolvent cubic equation
	Function temp_function({ 
		0.0, 
		1.0, 
		-c, 
		b * d - 4.0 * e, 
		4.0 * c * e - pow(d, 2) - pow(b, 2) * e 
	});
	temp_function.solve();
	const complex<double> y{ format_complex(temp_function.roots().at(0))};
	
	// Calculate the necessary constants to calculate the roots
	const complex<double> R{ format_complex(sqrt(1.0 / 4.0 * pow(b, 2) - c + y)) };
	const complex<double> D{ format_complex(
		abs(R) < epsilon ?
		sqrt(3.0 / 4.0 * pow(b, 2) - 2.0 * c + 2.0 * sqrt(pow(y, 2) - 4.0 * e)) 
		: sqrt(3.0 / 4.0 * pow(b, 2) - pow(R, 2) - 2.0 * c + 1.0 / 4.0 * (4.0 * b * c - 8.0 * d - pow(b, 3)) * pow(R, -1)) 
	) };
	const complex<double> E{ format_complex(
		abs(R) < epsilon ?
		sqrt(3.0 / 4.0 * pow(b, 2) - 2.0 * c - 2.0 * sqrt(pow(y, 2) - 4.0 * e)) 
		: sqrt(3.0 / 4.0 * pow(b, 2) - pow(R, 2) - 2.0 * c - 1.0 / 4.0 * (4.0 * b * c - 8.0 * d - pow(b, 3)) * pow(R, -1)) 
	) };

	// Calculate the roots
	const complex<double>	x1{ format_complex(-1.0 / 4.0 * b + 1.0 / 2.0 * R + 1.0 / 2.0 * D) },
							x2{ format_complex(-1.0 / 4.0 * b + 1.0 / 2.0 * R - 1.0 / 2.0 * D) },
							x3{ format_complex(-1.0 / 4.0 * b - 1.0 / 2.0 * R + 1.0 / 2.0 * E) },
							x4{ format_complex(-1.0 / 4.0 * b - 1.0 / 2.0 * R - 1.0 / 2.0 * E) };

	vector roots{ x1, x2, x3, x4 };
	for (const auto& root : roots) {
		if (abs(root.imag()) < epsilon)
			roots_.push_back(root.real());
	}
}