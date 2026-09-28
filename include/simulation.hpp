#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "body.hpp"
#include <vector>

namespace nbody {

void update_physics(std::vector<Body>&, Parameters);

}

#endif