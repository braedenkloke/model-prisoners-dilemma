#ifndef PRISONER_STATE_HPP
#define PRISONER_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

struct prisonerState {
	bool c; // True if prisoner cooperates, false if prisoner defects.

	// Default constructor function.
	prisonerState() : c(false) {}
};

// Prints the prisoner's state in an output stream.
std::ostream& operator<<(std::ostream& os, const prisonerState& x) {
	os << "<" << ((x.c)? 1 : 0) << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const prisonerState& x, const prisonerState& y) {
	return x.c != y.c;
}

// It parses a JSON file and generates the corresponding prisonerState object.
void from_json(const nlohmann::json& j, prisonerState& s) {
	j.at("c").get_to(s.c);
}

#endif // PRISONER_STATE_HPP
