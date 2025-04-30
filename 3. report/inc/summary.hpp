#pragma once
/*! \file	    summary.hpp
	\brief	    Function declarations for reporting the summary
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

#include "../../2. solution/solution.hpp"
#include "../../1. arguments/arguments.hpp"
#include <map>

namespace polyanalyzer {
	/*	\brief		Print the x row of the variation table
		\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
													  representing either the function or the derivative
					size_t							- The size of the left width
					size_t							- The size of the unit scale
	*/
	void print_x_row(const std::map<double, int>& roots, size_t left_width, size_t unit_scale);

	/*	\brief		Print the f'(x) row of the variation table
		\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
													  representing either the function or the derivative
					size_t							- The size of the left width
					size_t							- The size of the unit scale
					const Function&					- The derivative Function object
	*/
	void print_derivative_row(const std::map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& derivative);

	/*	\brief		Print the f(x) row of the variation table
		\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
													  representing either the function or the derivative
					size_t							- The size of the left width
					size_t							- The size of the unit scale
					const Function&					- The function Function object
	*/
	void print_function_row(const std::map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& function);

	/*	\brief		Print the variation table of the polynomial
		\param		const Function&	- The function Function object
					const Function&	- The derivative Function object
					const Argument&	- The Argument object
	*/
	void print_summary(const Function& function, const Function& derivative, const Argument& arguments);
}	// End of space polyanalyzer