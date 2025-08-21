/*! \file	    helper.cpp
	\brief	    Helper utilities
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

#include "../inc/constants.hpp"
#include "../inc/helper.hpp"
#include "../inc/system.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;

namespace polyanalyzer {
	// === 1. Numbers operation functions ==========================
	double ston(const string& number) {
		istringstream ss(number);

		if (regex_match(number, regex(R"mkv([-+]?\d+/\d+)mkv"))) {
			double numerator, denominator;
			char slash;
			ss >> numerator >> slash >> denominator;
			return numerator / denominator;
		}
		else if (regex_match(number, regex(R"mkv([-+]?\d*\.?\d*)mkv"))) {
			return stod(number);
		}
		//else if (regex_match(number, regex(R"mkv([-+]?\d+[-+]\d+i)mkv"))) {
		//	double real, imaginary;
		//	char oparator, i;
		//	ss >> real >> oparator >> imaginary >> i;
		//	if (oparator == '-')
		//		imaginary = -imaginary;
		//	return complex<double>(real, imaginary);
		//}
		else {
			throw invalid_argument("Invalid number format");
		}
	}

	// === 2. UTF-8 String functions ===============================
	size_t UTF8_size(const string& s) {
		size_t size{ 0 };
		for (char c : s)
			/*	- In UTF-8, a character starts with a byte that does not begin with binary 10
				- If c starts with 10, c & 0xC0 equals 0x80, which is a continuation byte
			*/
			if ((c & 0xC0) != 0x80)
				++size;

		return size;
	}

	string UTF8_string(size_t length, const string& c) {
		string s;
		for (size_t i{ 0 }; i < length; ++i)
			s += c;
		return s;
	}

	// === 3. Helper functions =====================================
	void print_title() {
		// Save the current color
		save_color();
		atexit(restore_color);

		// Set the codepage to 850
		SetConsoleOutputCP(CP_UTF8);
		atexit(restore_codepage);

		set_color(INVERSE_GREY);
		cout << " polyanalyzer 1.0.0 "s << copyright << "2024-2025, Manh Khang Vu "s;
		set_color(WHITE); cout << "\n\n";
	}

	void print_header(const string& title) {
		set_color(INVERSE_WHITE); cout << " " << setw(horizontal_width) << left << title << right;
		set_color(WHITE); cout << "\n\n";
	}
}	// End of namespace polyanalyzer