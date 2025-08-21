#pragma once
/*! \file	    Argument.hpp
	\brief	    Argument class declaration
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

#include <array>

namespace polyanalyzer {
	class Argument {
		bool help_;
		bool verbose_;
		std::array<double, 5> coefficients_;
	public:
		// Constructor
		Argument() : help_{ false }, verbose_{ false }, coefficients_{} {}

		// Accessors
		constexpr inline bool help() const { return help_; }
		constexpr inline bool verbose() const { return verbose_; }
		inline std::array<double, 5> coefficients() const { return coefficients_; }

		// Method
		/*	\brief		Parse the command line arguments
			\param		int		- The count of the arguments
						char*	- The pointer to the arguments
		*/
		void parse(int argc, char* argv[]);
	};
}	// End of namespace polyanalyzer