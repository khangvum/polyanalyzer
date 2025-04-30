#pragma once
/*! \file	    verbose.hpp
	\brief	    Function declarations for reporting the verbose
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

namespace polyanalyzer {
	// 1. x intersections (Roots)
	/*	\brief		Print the x intersections of the polynomial
		\param		const Function& - The function Function object
	*/
	void print_x_intersections(const Function& function);

	// 2. y intersection
	/*	\brief		Print the y intersection of the polynomial
		\param		const Function& - The function Function object
	*/
	void print_y_intersection(const Function& function);

	// 3. Domain
	/*	\brief		Print the domain of the polynomial
	*/
	void print_domain();

	// 4. Range
	/*	\brief		Print the range of the polynomial
		\param		const Function& - The function Function object
					const Function& - The derivative Function object
	*/
	void print_range(const Function& function, const Function& derivative);

	// 5. Extrema (Minima & Maxima)
	/*	\brief		Print the extrema (minima & maxima) of the polynomial
		\param		const Function& - The function Function object
					const Function& - The derivative Function object
	*/
	void print_min_max(const Function& function, const Function& derivative);

	// 6. Even & odd symmetry
	/*	\brief		Print the even & odd symmetry of the polynomial
		\param		const Function& - The function Function object
					const Function& - The derivative Function object
	*/
	void print_even_odd(const Function& function);

	/*	\brief		Print the verbose of the polynomial
		\param		const Function& - The function Function object
					const Function& - The derivative Function object
	*/
	void print_verbose(const Function& function, const Function& derivative);
}	// End of namespace polyanalyzer