#ifndef NBODY_BODY_HPP
#define NBODY_BODY_HPP

#include "config.hpp"
#include "vector3d.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace nbody {

class Body
{
 private:
  double mass_{1.e6};
  double rad_{1.e4};
  Vector3D<double> pos_{};
  Vector3D<double> vel_{};

 public:
  Body(double m, double r, Vector3D<double> p, Vector3D<double> v)
      : mass_{m}
      , rad_{r}
      , pos_{p}
      , vel_{v}
  {
    if (m <= 0) {
      throw std::runtime_error(
          "Mass of a body can't be less or equal to zero.\n");
    }
    if (r <= 0) {
      throw std::runtime_error(
          "Radius of a body can't be less or equal to zero.\n");
    }
  }

  Body update(std::vector<Body>, Parameters);

  
};

} // namespace nbody
#endif