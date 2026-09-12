#include "simulation.hpp"
#include "config.hpp"
#include <vector>

namespace nbody {

void update_physics(std::vector<Body>& universe, Parameters params)
{
  // modifica le collsion! (se a contatto li fondi)

  std::vector<Body> next_universe;
  next_universe.reserve(universe.size());

  for (auto& body : universe) {
    next_universe.push_back(body.update(universe, params));
  }

  universe = std::move(next_universe);
}

} // namespace nbody