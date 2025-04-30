#pragma once
/*! \file	    Function.hpp
	\brief	    Function class declaration
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

#include "../../0. utilities/utilities.hpp"
#include <array>
#include <vector>

namespace polyanalyzer {
	class Function {
		std::array<double, 5> coefficients_;
		std::vector<double> roots_;
	public:
		// Constructor
		Function(std::array<double, 5> coefficients) : coefficients_{ coefficients }, roots_{} {}

		// Accessors
		inline std::array<double, 5> coefficients() const { return coefficients_; }
		inline std::vector<double> roots() const { return roots_; }

		// Methods
		/*	\brief		Calculate the value of the function at a given x
			\param		double - The x value
			\return		double - The value of the function at x
		*/
		inline double value(double x) const {
			auto [a, b, c, d, e] { coefficients_ };
			return a * pow(x, 4) + b * pow(x, 3) + c * pow(x, 2) + d * x + e;
		}

		/*	\brief		Solve the function
		*/
		void solve();

		/*	\brief		Get the derivative of the function
		*/
		Function derivative() const;
	private:
		/*	\brief		Solve the linear function
		*/
		void solve_linear(double a, double b);

		/*	\brief		Solve the quadratic function
		*/
		void solve_quadratic(double a, double b, double c);

		/*	\brief		Solve the cubic function
		*/
		void solve_cubic(double a, double b, double c, double d);

		/*	\brief		Solve the quartic function
		*/
		void solve_quartic(double a, double b, double c, double d, double e);
	};
}	// End of namespace polyanalyzer