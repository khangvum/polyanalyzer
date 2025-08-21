#pragma once
/*! \file	    args.hpp
	\brief	    Function declarations for handling command line arguments
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

namespace polyanalyzer {
	/*	\brief		Print the help message if there is a -h or --help switch
	*/
	void print_help();
}	// End of namespace polyanalyzer