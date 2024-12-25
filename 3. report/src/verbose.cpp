/*! \file	    verbose.cpp
	\brief	    Function definitions for reporting the verbose
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

#include "../inc/verbose.hpp"
#include "../report.hpp"
#include <iostream>
#include <iomanip>
#include <set>
using namespace std;

void print_x_intersections(const Function& function) {
	const vector<double> func_roots{ function.roots() };

	// If there are no roots, do nothing
	if (func_roots.empty())
		return;

	string title{ "Intersection" + string(func_roots.size() > 1 ? "s" : "") + " with the x-axis" };
	for (size_t i{ 0 }; i < func_roots.size(); ++i) {
		// Print the title
		cout << " ";
		if ((func_roots.size() % 2 == 0 && i == func_roots.size() / 2 - 1)
			|| (func_roots.size() % 2 == 1 && i == func_roots.size() / 2)) {
			set_color(GREEN); cout << title;
			set_color(WHITE);
		}
		else {
			set_color(WHITE); cout << setw(title.size()) << "";
		}

		// Print the roots
		cout << "\t(";
		set_color(YELLOW); cout << format_number(func_roots.at(i));
		set_color(WHITE); cout << "; 0)\n\n";
	}
}

void print_y_intersection(const Function& function) {
	set_color(GREEN); cout << " " << "Intersection with the y-axis";
	set_color(WHITE); cout << "\t(0; ";
	set_color(YELLOW); cout << format_number(function.value(0.0));
	set_color(WHITE); cout << ")\n\n";
}

void print_domain() {
	set_color(GREEN); cout << " " << "Domain";
	set_color(WHITE); cout << "\t x " << element_of << " ";
	set_color(YELLOW); cout << R;
	set_color(WHITE); cout << "\n\n";
}

void print_range(const Function& function, const Function& derivative) {
	ostringstream low, high;

	// Calculate the limits & check if the range is infinite
	const string left_limit{ calculate_limit(function, false) }, right_limit{ calculate_limit(function) };
	if (left_limit == "-" + string(infinity) || right_limit == "-" + string(infinity))
		low << "-" << infinity;
	if (left_limit == "+" + string(infinity) || right_limit == "+" + string(infinity))
		high << "+" << infinity;

	set_color(GREEN); cout << " " << "Range";
	set_color(WHITE); cout << "\t y ";
	// If both bounds are empty, the range is constant
	if (low.str().empty() && high.str().empty()) {
		cout << "= ";
		set_color(YELLOW); cout << format_number(stod(left_limit)) << "\n\n";
		set_color(WHITE);
		return;
	}
	
	// Else (The range is finite and not constant)
	set<double> values;
	for (const double& root : derivative.roots())
		values.insert(function.value(root));

	if (low.str().empty())
		low << format_number(*values.begin());
	if (high.str().empty())
		high << format_number(*values.rbegin());

	cout << element_of;
	/*set_color(WHITE);*/ cout << (low.str() == "-" + string(infinity) ? " (" : " [");
	set_color(YELLOW); cout << low.str();
	set_color(WHITE); cout << "; ";
	set_color(YELLOW); cout << high.str();
	set_color(WHITE); cout << (high.str() == "+" + string(infinity) ? ")" : "]") << "\n\n";
}

void print_min_max(const Function& function, const Function& derivative) {
	const list<double> value_table{ get_value_table(derivative) };

	vector<pair<double, double>> minima, maxima;
	for (auto it{ next(begin(value_table)) }; it != end(value_table); advance(it, 2)) {
		if (*prev(it) < 0.0 && *next(it) > 0.0)
			minima.push_back(make_pair(*it, function.value(*it)));
		else
			maxima.push_back(make_pair(*it, function.value(*it)));
	}

	// Print the minima
	string title{ "Minim" + string(minima.size() > 1 ? "a" : "um") };
	print_extrema(minima, title);

	// Print the maxima
	title = "Maxim" + string(maxima.size() > 1 ? "a" : "um");
	print_extrema(maxima, title);
}

void print_even_odd(const Function& function) {
	const array<double, 5> coefficients{ function.coefficients() };

	// Check if the function is even or odd
	bool is_even{ true }, is_odd{ true };
	for (size_t i{ 0 }; i < coefficients.size(); ++i) {
		double coefficient{ coefficients.at(i) };
		if (abs(coefficient - coefficient * pow(-1, 4 - i)) > epsilon)
			is_even = false;
		if (abs(coefficient + coefficient * pow(-1, 4 - i)) > epsilon)
			is_odd = false;

		// If the function is neither even nor odd, break
		if (!is_even && !is_odd)
			break;
	}

	// Print the even/odd result
	set_color(GREEN); cout << " Even/Odd function";
	set_color(YELLOW); cout << "  ";
	if (is_even)
		cout << "Even\n\n";
	else if (is_odd)
		cout << "Odd\n\n";
	else
		cout << "None\n\n";
	set_color(WHITE);
}

void print_verbose(const Function& function, const Function& derivative) {
	// Print the header
	print_header("Details");

	// 1. Print the x intersections (roots)
	print_x_intersections(function);
	// 2. Print the y intersection
	print_y_intersection(function);
	// 3. Print the domain
	print_domain();
	// 4. Print the range
	print_range(function, derivative);
	// 5. Print the extrema (minima & maxima)
	print_min_max(function, derivative);
	// 6. Print the even & odd symmetry
	print_even_odd(function);
}