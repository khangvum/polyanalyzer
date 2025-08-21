/*! \file	    verbose_utilities.cpp
	\brief	    Verbose utilities
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

#include "../inc/verbose_utilities.hpp"
#include "../report.hpp"
#include <iostream>
#include <iomanip>
#include <numeric>		// For std::midpoint
using namespace std;

namespace polyanalyzer {
	list<double> get_value_table(const Function& derivative) {
		const vector<double> deri_roots{ derivative.roots() };
		list<double> value_table(begin(deri_roots), end(deri_roots));
		value_table.push_back(*rbegin(value_table) + 42.0);

		for (auto it{ begin(value_table) }; it != end(value_table); ++it) {
			double local_value;
			if (it == begin(value_table))
				local_value = derivative.value(*it - 1.0);
			else
				local_value = derivative.value(midpoint(*prev(it), *it));

			value_table.insert(it, local_value < 0.0 ? -1.0 : 1.0);
		}
		value_table.pop_back();

		return value_table;
	}

	void print_extrema(const vector<pair<double, double>>& extrema, const string& title) {
		if (extrema.empty())
			return;

		for (size_t i{ 0 }; i < extrema.size(); ++i) {
			// Print the title
			cout << " ";
			if ((extrema.size() % 2 == 0 && i == extrema.size() / 2 - 1)
				|| (extrema.size() % 2 == 1 && i == extrema.size() / 2)) {
				set_color(GREEN); cout << title;
				set_color(WHITE);
			}
			else {
				set_color(WHITE); cout << setw(title.size()) << "";
			}

			// Print the extrema
			cout << (title.size() == 7 /* Equals 1 tab */ ? " " : "\t ") << "(";
			set_color(YELLOW); cout << format_number(extrema.at(i).first);
			set_color(WHITE); cout << "; ";
			set_color(YELLOW); cout << format_number(extrema.at(i).second);
			set_color(WHITE); cout << ")\n\n";
		}
	}
}	// End of namespace polyanalyzer