/*! \file	    quadratic.cpp
	\brief	    Definition for quadratic equation solving function
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
#include <cmath>
using namespace std;

void Function::solve_quadratic(double a, double b, double c) {
	// Calculate the discriminant
	const double delta{ pow(b, 2) - 4.0 * a * c };

	// Calculate the roots based on the discriminant
	if (delta < 0.0)
		return;
	else if (delta > 0.0) {
		const double x1{ (-b + sqrt(delta)) / (2.0 * a) };
		const double x2{ (-b - sqrt(delta)) / (2.0 * a) };
		roots_ = move(vector<double>{ x1, x2 });
	}
	else
		roots_.push_back(- b / (2.0 * a));
}