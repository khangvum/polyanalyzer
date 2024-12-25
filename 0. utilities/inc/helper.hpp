#pragma once
/*! \file	    helper.hpp
	\brief	    Helper utilities
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

#include "constants.hpp"
#include <string>
#include <cmath>
#include <complex>

// === 1. Numbers operation functions ==========================
/*	\brief		Convert a string to a number
	\param		const std::string&	- The string representation of the number
	\return		double				- The number as a double
*/
double ston(const std::string& number);

/*	\brief		Override the cbrt function for complex numbers
	\param		const std::complex<double>&	- The complex number that needs to be cubed
	\return		std::complex<double>		- The cube root of the complex number
*/
inline std::complex<double> cbrt(const std::complex<double>& z) {
	/*	- pow(negative, fraction) is not well-defined:
			+ It will return a complex number.
			+ We will need to use the cbrt() function to handle this case.
		- cbrt(negative): 
			+ Returns a complex number with the imaginary part being 0, which is not what we want.
			+ Therefore, we have to use -cbrt(-z.real()) in order to preserve the sign.
	*/
	return z.imag() == 0 && z.real() < 0 ? -cbrt(-z.real()) : pow(z, 1.0 / 3.0);
}

/*	\brief		Handle precision errors in complex numbers when comparing with 0
	\param		const std::complex<double>&	- The complex number that needs formatting
	\return		std::complex<double>		- The formatted complex number
*/
inline std::complex<double> format_complex(const std::complex<double>& c) {
	double real{ abs(c.real()) < epsilon ? 0.0 : c.real() };
	double imag{ abs(c.imag()) < epsilon ? 0.0 : c.imag() };
	return std::complex<double>(real, imag);
}

// === 2. UTF-8 String functions ===============================
/*	\brief		Calculate the size of a UTF-8 string (Not the byte size)
	\param		const std::string&	- The string that needs calculating its size
	\return		size_t				- The size of the string
*/
size_t UTF8_size(const std::string& s);

/*	\brief		Create a string with a specific number of UTF-8 string (Replicate the string class's constructor)
	\param		size_t				- The length of the string
				const std::string&	- The UTF-8 string to create the new string
	\return		std::string			- The newly created string
*/
std::string UTF8_string(size_t length, const std::string& c);

// === 3. Helper functions =====================================
/*	\brief		Print the title of the program
*/
void print_title();

/*	\brief		Print the header of each section
	\param		const std::string&	- The title of the section
*/
void print_header(const std::string& title);