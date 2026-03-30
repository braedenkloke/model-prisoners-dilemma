#ifndef PRISONER_CELL_HPP
#define PRISONER_CELL_HPP

#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "prisoner_state.hpp"

using namespace cadmium::celldevs;

class conway : public GridCell<prisonerState, double> {

	public:
	conway(const std::vector<int>& id, 
           const std::shared_ptr<const GridCellConfig<prisonerState, double>>& config
    ): GridCell<prisonerState, double>(id, config) { }

	[[nodiscard]] prisonerState localComputation(
        prisonerState state,
        const std::unordered_map<std::vector<int>, NeighborData<prisonerState, double>>& neighborhood
    ) const override {
        // Play the Prisoner's Dilemma with each neighbor, 
        // Prisoner's are assumed to be neighbors of themselves
		for (const auto& [neighborId, neighborData]: neighborhood) {
			auto nState = neighborData.state;
            if (state.cooperate == true && nState->cooperate == true) {
                state.total_payoff += state.r; // Reward
            } else if (state.cooperate == true && nState->cooperate == false) {
                state.total_payoff += state.s; // Sucker's payoff
            } else if (state.cooperate == false && nState->cooperate == true) {
                state.total_payoff += state.t; // Temptation payoff
            } else {
                state.total_payoff += state.p; // Punishment
            }
        }

        // Remove payoff gained from this Prisoner playing against itself
        if (state.cooperate) {
            state.total_payoff -= state.r; // Reward
        } else {
            state.total_payoff -= state.p; // Punishment
        }
		return state;
	}

	[[nodiscard]] double outputDelay(const prisonerState& state) const override {
		return 1.;
	}
};

#endif // PRISONER_CELL_HPP
