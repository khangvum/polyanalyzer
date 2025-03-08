/*! \file	    summary_utilities.cpp
	\brief	    Summary utilities
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

#include "../inc/summary_utilities.hpp"
#include "../report.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>		// For std::midpoint
using namespace std;

// 1. print_derivative_values's helper functions
char get_sign(double value) { return abs(value) < epsilon ? '0' : value < 0.0 ? '-' : '+'; }

list<pair<char, streamsize>> calculate_value_ranges(const map<double, int>& roots, size_t unit_scale, const Function& derivative) {
	// Calculate the necessary values that cannot be captured by the arguments, yet easy to calculate again
	vector<double>	deri_roots{ derivative.roots() };
	const string	left_limit{ calculate_limit(derivative, false) }, 
					right_limit{ calculate_limit(derivative) };

	// 1. Get the signs of the value ranges between the roots
	list<pair<char, streamsize>> value_ranges;

	streamsize	value_width{ static_cast<streamsize>(2 * UTF8_size(left_limit)) }, 
				previous_value_width{ value_width },
				final_width{ 0 },
				total_width{ 0 };
	for (auto it{ begin(roots) }; it != end(roots); ++it) {
		previous_value_width = value_width;
		value_width = 1;
		final_width += unit_scale - (previous_value_width - previous_value_width / 2) - value_width / 2;
		if (it->second < 1) {
			value_ranges.push_back(make_pair('0', final_width));
			total_width += final_width + 1;	// 1 is for the width of '0'
			final_width = 0;
		}
		else
			++final_width;	// The width of the ' ' value if the current x is not a root of the derivative
	}
	// The last value range to reach the right limit
	final_width = unit_scale * (roots.size() + 1) - total_width - UTF8_size(right_limit);
	value_ranges.push_back(make_pair('X', final_width));	  // 'X' is just a placeholder

	// 2. Calculate the widths between the values and the signs
	// Push back a placeholder to calculate the width of the last value range (Before the right limit)
	deri_roots.push_back(*rbegin(deri_roots) + 42.0);

	// As the iterators for the value_ranges and the deri_roots are different types, we need to declare them separately
	list<pair<char, streamsize>>::iterator ranges_it{ begin(value_ranges) };
	vector<double>::iterator roots_it{ begin(deri_roots) };
	for (; ranges_it != end(value_ranges) && roots_it != end(deri_roots); ++ranges_it, ++roots_it) {
		char sign;
		if (ranges_it == begin(value_ranges))
			sign = get_sign(derivative.value(*roots_it - 1.0));
		else
			sign = get_sign(derivative.value(midpoint(*prev(roots_it), *roots_it)));

		streamsize total_width{ ranges_it->second };
		ranges_it->second = total_width / 2;
		value_ranges.insert(ranges_it, make_pair(sign, total_width - total_width / 2 - 1));
	}

	// Pop back the placeholder
	deri_roots.pop_back();

	return value_ranges;
}

// 2. print_function_values's helper functions
void print_infinity_row(const map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& function, bool is_positive) {
	const char sign{ is_positive ? '+' : '-' };
	
	// Calculate the limits
	const string	left_limit{ calculate_limit(function, false) }, 
					right_limit{ calculate_limit(function) };

	// Print the left column of the infinity row
	print_left_column(left_width);

	// Print the infinity row
	set_color(YELLOW);
	cout << (left_limit == sign + string(infinity) ? left_limit : string(UTF8_size(left_limit), ' '))
		<< setw(unit_scale * (roots.size() + 1) - UTF8_size(left_limit) - UTF8_size(right_limit)) << ""
		<< (right_limit == sign + string(infinity) ? right_limit : string(UTF8_size(right_limit), ' '));
	set_color(WHITE);
}

void print_values_row(const map<double, int>& roots, size_t left_width, size_t unit_scale, const Function& function, bool is_positive) {
	const double sign{ is_positive ? 1.0 : -1.0 };

	// Calculate the limits
	const string	left_limit{ calculate_limit(function, false) }, 
					right_limit{ calculate_limit(function) };

	// Print the values of the function at the roots
	// - Determine which values are larger to be printed at the top row, and which are smaller to be printed at the bottom row
	vector<pair<double, double>> values(roots.size());

	size_t previous_index{ 0 };
	bool is_first_value{ true };
	for (auto it{ begin(roots) }; it != end(roots); ++it) {
		auto index{ distance(begin(roots), it) };
		double value{ it->second < 1 ? function.value(it->first) : 0.0 };

		// If the value is not in the positive/negative range, continue
		if (sign * value <= epsilon) continue;

		values.at(index).first = value;
		if (!is_first_value) {
			double	previous_top_value{ abs(values.at(previous_index).first) }, 
					previous_bottom_value{ abs(values.at(previous_index).second) };

			// If the previous value is at the top row
			if (previous_top_value > previous_bottom_value) {
				double previous_value{ values.at(previous_index).first };
				if (abs(previous_value - value) < epsilon)
					continue;
				else if (previous_value < value)
					swap(values.at(previous_index).first, values.at(previous_index).second);
				else
					swap(values.at(index).first, values.at(index).second);
			}
			// Else if, the previous value is at the bottom row
			else if (previous_top_value < previous_bottom_value) {
				double previous_value{ values.at(previous_index).second };
				if (abs(previous_value - value) < epsilon)
					continue;
				else if (previous_value > value) {
					swap(values.at(previous_index).first, values.at(previous_index).second);
					swap(values.at(index).first, values.at(index).second);
				}
			}
		}
		else
			is_first_value = false;
		
		previous_index = index;
	}

	// - Print the values
	auto bottom_value_count{ count_if(begin(values), end(values), [](const pair<double, double>& value) { return abs(value.second) > epsilon; }) };
	for (size_t r{ 0 }; ; ++r) {
		// Print the left column of the values row
		print_left_column(left_width);

		// Print the left limit (If it is not infinity)
		set_color(YELLOW);
		cout << (left_limit.find(infinity) == string::npos && sign * stod(left_limit) > 0.0 ? left_limit : string(UTF8_size(left_limit), ' '));

		// Print the values
		// - If the function is constant
		if (values.size() == 0)
			cout << setw(unit_scale * (roots.size() + 1) - UTF8_size(left_limit) - UTF8_size(right_limit)) << "";
		// - Else
		set_color(CYAN);
		streamsize value_width{ static_cast<streamsize>(2 * UTF8_size(left_limit)) };
		for (size_t i{ 0 }; i < values.size(); ++i) {
			streamsize previous_value_width{ value_width };

			double value{ r == 0 ? values.at(i).first : values.at(i).second };
			string value_str{ format_number(value) };
			value_width = sign * value > 0.0 ? value_str.size() : 0;

			cout << setw(unit_scale - (previous_value_width - previous_value_width / 2) - value_width / 2) << "" 
				<< (sign * value > 0.0 ? value_str : "");
		}

		// Print the right limit (If it is not infinity)
		set_color(YELLOW);
		cout << (right_limit.find(infinity) == string::npos && sign * stod(right_limit) > 0.0 ? right_limit : string(UTF8_size(right_limit), ' '));
		set_color(WHITE);

		if (bottom_value_count == 0 || r == 1)
			break;
		
		cout << "\n";
	}
}

void print_zero_row(const map<double, int>& roots, size_t left_width, size_t unit_scale) {
	// Print the left column of the infinity row
	print_left_column(left_width, string(f) + "(x)");

	// Print the zero values row
	streamsize value_width{ 0 };
	for (auto it{ begin(roots) }; it != end(roots); ++it) {
		//set_color(RED); cout << UTF8_string(unit_scale - (value_width - value_width / 2) - 1, dash);
		streamsize previous_value_width{ value_width };
		
		set_color(RED);
		cout << UTF8_string(unit_scale - (previous_value_width - previous_value_width / 2) - value_width / 2 - (value_width + 1), dash);

		value_width = 1;

		set_color(it->second == 0 ? CYAN : it->second == 1 ? WHITE : RED);
		cout << (it->second > -1 ? " 0 " : UTF8_string(3, dash));
	}
	set_color(RED); cout << UTF8_string(unit_scale - (value_width - value_width / 2) - 1, dash) << "> y=0";
	set_color(WHITE);
}