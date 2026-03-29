#ifndef PRISONER_STATE_HPP
#define PRISONER_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

struct prisonerState {
	bool cooperate; // True if prisoner cooperates, false if prisoner defects.
    int years_free;

	// Default constructor function.
	prisonerState() : cooperate(false), years_free(0) {}
};

// Prints the prisoner's state in an output stream.
std::ostream& operator<<(std::ostream& os, const prisonerState& x) {
	os << "<" << ((x.cooperate)? 1 : 0) << "," << x.years_free << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const prisonerState& x, const prisonerState& y) {
	return x.cooperate != y.cooperate;
}

// It parses a JSON file and generates the corresponding prisonerState object.
void from_json(const nlohmann::json& j, prisonerState& s) {
	j.at("cooperate").get_to(s.cooperate);
	j.at("years_free").get_to(s.years_free);
}

#endif // PRISONER_STATE_HPP
