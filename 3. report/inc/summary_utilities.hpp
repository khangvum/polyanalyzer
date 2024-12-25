#pragma once
/*! \file	    summary_utilities.hpp
	\brief	    Summary utilities
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
#include <list>
#include <map>

// 1. print_derivative_values's helper functions
/*	\brief		Get the sign of a number that represents its value range
	\param		double	- The number that needs to get the sign
	\return		char	- The sign of the number
*/
char get_sign(double number);

/*	\brief		Get the signs of the value ranges, and their corresponding widths to be printed
	\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
												  representing either the function or the derivative
				size_t							- The size of the left width
				size_t							- The size of the unit scale
				const Function&					- The derivative Function object
	\return		std::list<std::pair<char, std::streamsize>>	- A list of pairs of the signs and widths
*/
std::list<std::pair<char, std::streamsize>> calculate_value_ranges(const std::map<double, int>& roots, size_t unit_scale, const Function& derivative);

// 2. print_function_values's helper functions
/*	\brief		Print the infinity row of the function row
	\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
												  representing either the function or the derivative
				size_t							- The size of the left width
				size_t							- The size of the unit scale
				const Function&					- The function Function object
				bool							- The side of the range
*/
void print_infinity_row(const std::map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& function, bool is_positive = true);

/*	\brief		Print the value row of the function row
	\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
												  representing either the function or the derivative
				size_t							- The size of the left width
				size_t							- The size of the unit scale
				const Function&					- The function Function object
				bool							- The side of the range
*/
void print_values_row(const std::map<double, int>& roots, size_t unit_scale, size_t left_width, const Function& function, bool is_positive = true);

/*	\brief		Print the zero row of the function row
	\param		const std::map<double, int>&	- The map of the roots and their corresponding ints
												  representing either the function or the derivative
				size_t							- The size of the left width
				size_t							- The size of the unit scale
*/
void print_zero_row(const std::map<double, int>& roots, size_t left_width, size_t unit_scale);