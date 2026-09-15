#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "body.hpp"
#include "config.hpp"
#include <vector>

namespace nbody {

class SystemGenerator
{
 public:
  static std::vector<Body> solar_system();
  static std::vector<Body> KeplerianDisk(size_t count, double max_radius,
                                         double central_mass);
};

} // namespace nbody
#endif