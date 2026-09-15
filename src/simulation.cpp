#include "simulation.hpp"
#include "config.hpp"
#include <vector>

namespace nbody {

void update_physics(std::vector<Body>& universe, Parameters params)
{
  // First predict every position from the same old state.
  std::vector<Body> predicted{universe};
  for (std::size_t i = 0; i < universe.size(); ++i) {
    predicted[i] =
        universe[i].with_position(universe[i].compute_position(universe, params));
  }

  // Then evaluate acceleration at the predicted positions and correct velocity.
  std::vector<Body> next_universe{predicted};
  for (std::size_t i = 0; i < predicted.size(); ++i) {
    const Vector3D<double> new_acceleration =
        predicted[i].compute_acceleration(predicted, params);
    next_universe[i] =
        predicted[i].with_velocity_and_acceleration(new_acceleration, params);
  }

  universe = std::move(next_universe);
}

} // namespace nbody