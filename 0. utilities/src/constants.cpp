/*! \file	    constants.cpp
	\brief	    Useful constants
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

#include "../inc/constants.hpp"
#include <numbers>
using namespace std;

// === 2. Special characters in Codepage UTF-8 =================
// - Mathematical symbols
const unordered_map<size_t, const char*> superscripts{ {2, "\xC2\xB2"}, {3, "\xC2\xB3"}, {4, "\xE2\x81\xB4"} };
const unordered_map<size_t, const char*> subscripts{ {0, "\xE2\x82\x80"}, {1, "\xE2\x82\x81"}, {2, "\xE2\x82\x82"}, {3, "\xE2\x82\x83"}, {4, "\xE2\x82\x84"} };

// === 3. Numerical/ Mathematical constants ====================
const complex<double> u_plus(1.0 / 2.0, numbers::sqrt3 / 2.0),
u_minus(1.0 / 2.0, -numbers::sqrt3 / 2.0);