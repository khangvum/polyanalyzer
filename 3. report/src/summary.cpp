/*! \file	    summary.cpp
	\brief	    Function definitions for reporting the summary
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

#include "../inc/summary.hpp"
#include "../report.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

namespace polyanalyzer {
	void print_x_row(const map<double, int>& roots, size_t left_width, size_t unit_scale) {
		// Print the left column of the x row
		print_left_column(left_width, "x");

		// Print the roots
		cout << "-" << infinity;
		if (roots.size() == 0)
			cout << setw(unit_scale - 4) << "";
		else {
			set_color(CYAN);
			streamsize root_width{ 4 }; // The first (previous_root_width - previous_root_width / 2) = 2 for -inf
			// 3 also works, but 4 is more visually understandable
			for (const auto& root : roots) {
				string root_str{ format_number(root.first) };
				streamsize previous_root_width{ root_width };
				root_width = root_str.size();
				cout << setw(unit_scale - (previous_root_width - previous_root_width / 2) - root_width / 2) << "" << root_str;
			}
			cout << setw(unit_scale - (root_width - root_width / 2) - 2) << "";
			set_color(WHITE);
		}
		cout << "+" << infinity << "\n";
	}

	void print_derivative_row(const map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& derivative) {
		const vector<double> deri_roots{ derivative.roots() };

		// Print the left column of the f'(x) row
		// setw() operates on bytes, not the actual width of the string
		print_left_column(left_width, string(f) + "'(x)=" + get_function(derivative));

		// Calculate the limits
		const string left_limit{ calculate_limit(derivative, false) }, right_limit{ calculate_limit(derivative) };
		set_color(YELLOW); cout << left_limit;
		set_color(WHITE);

		// Print the values where the derivative is zero & the signs of the value ranges between the roots
		if (deri_roots.size() == 0) {
			size_t width{ unit_scale * (roots.size() + 1) - UTF8_size(left_limit) - UTF8_size(right_limit) };
			cout << setw(width - width / 2) << "" << get_sign(derivative.value(0.0)) << setw(width / 2 - 1) << "";
		}
		else {
			// Get the signs of the value ranges between the roots
			list<pair<char, streamsize>> value_ranges{ calculate_value_ranges(roots, unit_scale, derivative) };

			// Print the signs of the value ranges & the values where the derivative is zero
			for (auto it{ begin(value_ranges) }; it != prev(end(value_ranges)); ++it) {
				if (it->first != '0') {
					set_color(GREEN); cout << setw(it->second) << "" << it->first;
				}
				else {
					set_color(WHITE); cout << it->first;
				}

				if (it->first != '0' && it != prev(end(value_ranges), 2))
					cout << setw(next(it)->second) << "";
			}
			cout << setw(prev(end(value_ranges))->second - UTF8_size(right_limit)) << "";
		}

		set_color(YELLOW); cout << right_limit << "\n";
		set_color(WHITE);
	}

	void print_function_row(const map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& function) {
		const vector<double> func_roots{ function.roots() };

		// Calculate the limits
		const string left_limit{ calculate_limit(function, false) }, right_limit{ calculate_limit(function) };

		// Print the 5 rows of the f(x) row
		print_infinity_row(roots, left_width, unit_scale, function); cout << "\n";
		print_values_row(roots, left_width, unit_scale, function); cout << "\n";
		print_zero_row(roots, left_width, unit_scale); cout << "\n";
		print_values_row(roots, left_width, unit_scale, function, false); cout << "\n";
		print_infinity_row(roots, left_width, unit_scale, function, false); cout << "\n";
	}

	void print_summary(const Function& function, const Function& derivative, const Argument& arguments) {
		const string deri_expression{ string(f) + "'(x)=" + get_function(derivative) };

		// Calculate the widths of the columns & the horizontal width
		const vector<double>	func_roots{ function.roots() },
			deri_roots{ derivative.roots() };
		map<double, int> roots;
		for (double func_root : func_roots) ++roots[func_root];	// - Func_root is marked as 1
		for (double deri_root : deri_roots) --roots[deri_root];	// - Deri_root is marked as -1
		// - If both the function and the deri_expression share a root, 
		// the root is marked as 1 - 1 = 0

		const size_t	left_width{ UTF8_size(deri_expression) },
			unit_scale{ static_cast<size_t>(round(90 / (roots.size() + 1))) },
			right_width{ static_cast<size_t>(unit_scale * (roots.size() + 1) + 5) };	 // +5 is for the "> y=0" string

		const string horrizontal_line{ UTF8_string(left_width, dash) + cross + UTF8_string(right_width, dash) };
		horizontal_width = UTF8_size(horrizontal_line);

		// If there is a verbose request, print the details
		if (arguments.verbose() && !roots.empty())
			print_verbose(function, derivative);

		// Print the header
		print_header("Summary");

		// Print the variation table
		print_x_row(roots, left_width, unit_scale); cout << " " << horrizontal_line << "\n";
		print_derivative_row(roots, left_width, unit_scale, derivative); cout << " " << horrizontal_line << "\n";
		print_function_row(roots, left_width, unit_scale, function);
	}
}	// End of namespace polyanalyzer