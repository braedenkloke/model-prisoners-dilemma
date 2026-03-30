#ifndef PRISONER_STATE_HPP
#define PRISONER_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

struct prisonerState {
	bool cooperate; // True if prisoner cooperates, false if prisoner defects.
    int total_payoff;
    int r, s, t, p; // Payoff matrix

	// Default constructor function.
	prisonerState() : cooperate(false), total_payoff(0), r(3), s(0), t(5), p(1) {}
};

// Prints the prisoner's state in an output stream.
std::ostream& operator<<(std::ostream& os, const prisonerState& x) {
	os << "<" << ((x.cooperate)? 1 : 0) << "," << x.total_payoff << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const prisonerState& x, const prisonerState& y) {
	return x.total_payoff != y.total_payoff;
}

// It parses a JSON file and generates the corresponding prisonerState object.
void from_json(const nlohmann::json& j, prisonerState& s) {
	j.at("cooperate").get_to(s.cooperate);
}

#endif // PRISONER_STATE_HPP
