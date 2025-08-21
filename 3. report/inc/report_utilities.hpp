#pragma once
/*! \file	    report_utilities.hpp
	\brief	    Report utilities
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

namespace polyanalyzer {
	/*	\brief		Get the expression of the function
		\param		const Function&	- The function Function object
		\return		std::string		- The function expression
	*/
	std::string get_function(const Function& function);

	/*	\brief		Calculate the limit of the function
		\param		const Function&	- The function Function object
					bool			- The side of the limit
		\return		std::string		- The limit of the function
	*/
	std::string calculate_limit(const Function& function, bool is_positive = true);

	/*	\brief		Format the number as a string
		\param		double		- The number that needs formatting
		\return		std::string	- The formatted number
	*/
	std::string format_number(double number);

	/*	\brief		Print the left column of every row
		\param		size_t				- The width of the left column
					const std::string&	- The expression of the left column
	*/
	void print_left_column(size_t left_width, const std::string& expression = "");
}	// End of namespace polyanalyzer