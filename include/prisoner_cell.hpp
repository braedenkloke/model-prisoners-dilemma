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
        const std::unordered_map<std::vector<int>, 
        NeighborData<prisonerState, 
        double>>& neighborhood
    ) const override {
		int live_neighbors = 0;

		for (const auto& [neighborId, neighborData]: neighborhood) {
            // For each neighbor, calculate points
			auto nState = neighborData.state;

			if(nState->c == true) {
				live_neighbors++;
			}

		}

		if(state.c == true) {
			live_neighbors--; //Self is a neighbor, we do not care about that yet.
			if(live_neighbors < 2 || live_neighbors > 3) {
				state.c = false;
			}
		} else {
			if(live_neighbors == 3) {
				state.c = true;
			}
		}

		return state;
	}

	[[nodiscard]] double outputDelay(const prisonerState& state) const override {
		return 1.;
	}
};

#endif // PRISONER_CELL_HPP
