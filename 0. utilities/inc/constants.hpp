#pragma once
/*! \file	    constants.hpp
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

#include <Windows.h>
#include <string>
#include <unordered_map>
#include <complex>

// === 1. Color constants ======================================
//constexpr WORD GREY{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED };
constexpr WORD WHITE{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY }; // FOREGROUND_INTENSITY | GREY
constexpr WORD YELLOW{ FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY };
constexpr WORD CYAN{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY };
constexpr WORD GREEN{ FOREGROUND_GREEN | FOREGROUND_INTENSITY };
constexpr WORD RED{ FOREGROUND_RED | FOREGROUND_INTENSITY };
constexpr WORD INVERSE_WHITE{ BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY };
constexpr WORD INVERSE_GREY{ BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED };
constexpr WORD INVERSE_RED{ BACKGROUND_RED | BACKGROUND_INTENSITY };

// === 2. Special characters in Codepage UTF-8 =================
// - Mathematical symbols
constexpr char f[]{ "\xC6\x92" };
constexpr char infinity[]{ "\xE2\x88\x9E" };
constexpr char element_of[]{ "\xE2\x88\x88" };
constexpr char R[]{ "\xE2\x84\x9D" };
extern const std::unordered_map<size_t, const char*> superscripts;
extern const std::unordered_map<size_t, const char*> subscripts;
// - Other characters
constexpr char copyright[]{ "\xC2\xA9" };
constexpr char dash[]{ "\xE2\x94\x80" };
constexpr char cross[]{ "\xE2\x94\xBC" };
constexpr char bar[]{ "\xE2\x94\x82" };
constexpr char downward_T[]{ "\xE2\x94\xAC" };

// === 3. Numerical/ Mathematical constants ====================
constexpr double epsilon{ 1.0E-6 /* std::numeric_limits<double>::epsilon() */ };	// The epsilon value for comparing double values
extern const std::complex<double> u_plus, u_minus;	// The complex roots of unity