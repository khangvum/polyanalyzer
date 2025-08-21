/*! \file	    system.cpp
	\brief	    System utilities
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

#include "../inc/system.hpp"
using namespace std;

namespace polyanalyzer {
	CONSOLE_SCREEN_BUFFER_INFO csbi{ 0 };
	UINT codepage{ GetConsoleOutputCP() };
	size_t horizontal_width{};

	// === 1. Color functions ======================================
	void save_color() { GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); }

	void set_color(WORD attribute) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute); }

	void restore_color() { set_color(csbi.wAttributes); }

	// === 2. Codepage functions ===================================
	void restore_codepage() { SetConsoleOutputCP(codepage); }
}	// End of namespace polyanalyzer