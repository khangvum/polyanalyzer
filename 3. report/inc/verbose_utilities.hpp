#pragma once
/*! \file	    verbose_utilities.hpp
	\brief	    Verbose utilities
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

#include "../../2. solution/solution.hpp"
#include <list>

namespace polyanalyzer {
	/*	\brief		Get the value table of the derivative
		\param		const Function&		- The derivative Function object
		\return		std::list<double>	- The value table
	*/
	std::list<double> get_value_table(const Function& derivative);

	/*	\brief		Print the extrema of the polynomial
		\param		const std::vector<std::pair<double, double>>&	- The extrema of the polynomial
					const std::string&								- The title to be printed
	*/
	void print_extrema(const std::vector<std::pair<double, double>>& extrema, const std::string& title);
}	// End of namespace polyanalyzer