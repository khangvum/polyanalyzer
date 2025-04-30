/*! \file	    polyanalyzer.cpp
	\brief	    Analyze a polynomial
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

#include "polyanalyzer.hpp"
#include <iostream>
using namespace std;
using namespace polyanalyzer;

int main(int argc, char* argv[])
{
	// Create a Argument object to parse the arguments
	Argument arguments;
	arguments.parse(argc, argv);

	// Print the title
	print_title();

	// If there is a help request, print the help message and exit
	if (arguments.help()) {
		print_help();
		return EXIT_SUCCESS;
	}

	// Else, begin the program by solving the function
	Function function(arguments.coefficients());
	function.solve();
	Function derivative{ function.derivative() };
	derivative.solve();

	// Print the polynomial that needs analyzing
	set_color(INVERSE_RED); cout << " Polynomial: ";
	set_color(RED); cout << " " << f << "(x)=" << get_function(function);
	set_color(WHITE); cout << "\n\n";
	
	// Print the summary
	print_summary(function, derivative, arguments);
}