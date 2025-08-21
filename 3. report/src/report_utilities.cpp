/*! \file	    report_utilities.cpp
	\brief	    Report utilities
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

#include "../inc/report_utilities.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

namespace polyanalyzer {
	string get_function(const Function& function) {
		auto coefficients{ function.coefficients() };

		ostringstream result;
		(void)result.imbue(locale(""));

		bool first_coefficient{ true };
		for (size_t i{ 0 }; i < coefficients.size(); ++i) {
			double coefficient{ coefficients.at(i) };

			// If the coefficient is zero
			if (abs(coefficient) < epsilon)
				continue;
			// If the coefficient is 1 and it is not the leading coefficient nor the independent digit
			else if (abs(coefficient - 1.0) < epsilon && !first_coefficient && i != coefficients.size() - 1)
				result << "+";
			// If the coefficient is -1 and it is not the independent coefficient
			else if (abs(coefficient + 1.0) < epsilon && i != coefficients.size() - 1)
				result << "-";
			// If the coefficient is positive and it is not the leading coefficient
			else if (coefficient > 0.0 && !first_coefficient)
				result << "+" << format_number(coefficient);
			// If the coefficent is not 1 or is 1 but is the the independent coefficient
			else if (abs(coefficient - 1.0) > epsilon || i == coefficients.size() - 1)
				result << format_number(coefficient);

			// Print the x and its corresponding superscript
			result << (i != coefficients.size() - 1 ? "x" : "")
				<< (i < coefficients.size() - 2 ? string(superscripts.at(coefficients.size() - 1 - i)) : "");

			// If the last coefficient is not zero, set first_coefficient to false
			if (abs(coefficient) > epsilon)
				first_coefficient = false;
		}

		// If all coefficients are zero, the function is zero
		if (first_coefficient)
			result << 0;

		return result.str();
	}

	string calculate_limit(const Function& function, bool is_positive) {
		const array<double, 5> coefficients{ function.coefficients() };

		double leading_coefficient{ 0.0 };
		array<double, 5>::size_type i{ 0 };
		for (; i < coefficients.size(); ++i) {
			if (abs(coefficients.at(i)) > epsilon) {
				leading_coefficient = coefficients.at(i);
				break;
			}
		}

		double sign{ is_positive ? 1.0 : -1.0 };
		double limit{ leading_coefficient * pow(sign, i % 2) };

		if (i < coefficients.size() - 1)
			return (limit > 0 ? "+" : "-") + string(infinity);

		limit = leading_coefficient;
		ostringstream os;
		if (abs(limit - round(limit)) < epsilon						// Ensure that the limit is an integer
			&& (abs(limit) < epsilon || limit > 0 && limit < 10))	// Ensure that there is only 1 digit
			os << (is_positive ? " " : "") << limit << (is_positive ? "" : " ");
		else
			os << format_number(limit);

		return os.str();
	}

	string format_number(double number) {
		ostringstream os;
		os << setprecision(5);
		(void)os.imbue(locale(""));

		if (abs(abs(number) - 1'000) < epsilon || abs(number) > 1'000) {
			if (abs(number - round(number)) < epsilon || abs(number * 10 - round(number * 10)) < epsilon)
				os << number;
			else
				os << fixed << setprecision(2) << number;
		}
		else
			os << number;

		return os.str();
	}

	void print_left_column(size_t left_width, const string& expression) {
		size_t expression_width{ UTF8_size(expression) };

		set_color(GREEN);
		cout << " " << setw(left_width / 2 - expression_width / 2) << "" << expression << setw((left_width - left_width / 2) - (expression_width - expression_width / 2)) << "";
		set_color(WHITE); cout << bar;
	}
}	// End of namespace polyanalyzer