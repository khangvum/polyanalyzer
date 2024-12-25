/*! \file	    Argument.cpp
	\brief	    Argument class definition
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

#include "../inc/Argument.hpp"
#include "../../0. utilities/utilities.hpp"
#include <iostream>
#include <deque>
#include <regex>
#include <cstdlib>
using namespace std;

// Method
void Argument::parse(int argc, char* argv[]) {
	// Load the arguments, excluding the executable file name
	deque<string> args_deque(argv + 1, argv + argc);

	// Parse the arguments
	deque<string>::iterator args_it;
	for (args_it = begin(args_deque); args_it != end(args_deque); ++args_it) {
		if (*args_it == "--help") {
			help_ = true;
		}
		else if (regex_match(*args_it, regex("^-[a-z]+$"))) {
			for (const char& c : string(begin(*args_it) + 1, end(*args_it))) {
				switch (c) {
				case 'h': help_ = true; break;
				case 'v': verbose_ = true; break;
				}
			}
		}
		else {
			deque<double> coefficients;
			while (coefficients.size() != 5 && args_it != end(args_deque)) {
				try {
					coefficients.push_back(ston(*args_it++));
				}
				catch (const invalid_argument&) {
					cerr << "Error: Invalid argument: \"" << *--args_it << "\" is not a real number\n";
					exit(EXIT_FAILURE);
				}
			}

			// If there are not enough coefficients, fill the rest with 0s
			while (coefficients.size() != 5)
				coefficients.push_front(0.0);

			// Add the coefficients to the Argument object
			for (size_t i{ 0 }; i < coefficients.size(); ++i)
				coefficients_[i] = coefficients.at(i);

			break;
		}
	}

	if (args_it != end(args_deque) && !help_) {
		cerr << "Error: Error: Too many commandline arguments: " << *args_it << "...\n";
		exit(EXIT_FAILURE);
	}
}