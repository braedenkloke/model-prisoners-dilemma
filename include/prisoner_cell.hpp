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
		for (const auto& [neighborId, neighborData]: neighborhood) {
			auto nState = neighborData.state;
            if (state.cooperate == true && nState->cooperate == true) {
                // Both prisoners cooperate; Reward payoff
                state.years_free += 3;
            } else if (state.cooperate == true && nState->cooperate == false) {
                // Opponent defects; Sucker's payoff
                state.years_free += 0;
            } else if (state.cooperate == false && nState->cooperate == true) {
                // Opponent cooperates; Temptation payoff
                state.years_free += 5;
            } else {
                // Both prisoners defect; Punishment payoff
                state.years_free += 1;
            }
		}
		return state;
	}

	[[nodiscard]] double outputDelay(const prisonerState& state) const override {
		return 1.;
	}
};

#endif // PRISONER_CELL_HPP
