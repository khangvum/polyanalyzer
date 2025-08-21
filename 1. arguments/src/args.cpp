/*! \file	    args.cpp
	\brief	    Function definitions for handling command line arguments
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

#include "../inc/args.hpp"
#include "../../0. utilities/utilities.hpp"
#include <iostream>
using namespace std;

namespace polyanalyzer {
	void print_help() {
		SetConsoleOutputCP(CP_UTF8);
		cout << "\tUsage: polyanalyzer [--help] [-hv] [a] [b] [c] [d] [e]\n"s
			<< "\tswitches:\n"s
			<< "\t\th\thelp\n"s
			<< "\t\tv\tverbose\n"s
			<< "\targuments:\n"s
			<< "\t\ta\tcoefficient of x"s << superscripts.at(4) << "\n"
			<< "\t\tb\tcoefficient of x"s << superscripts.at(3) << "\n"
			<< "\t\tc\tcoefficient of x"s << superscripts.at(2) << "\n"
			<< "\t\td\tcoefficient of x\n"s
			<< "\t\te\tindepedent coefficient\n"s;
	}
}	// End of namespace polyanalyzer